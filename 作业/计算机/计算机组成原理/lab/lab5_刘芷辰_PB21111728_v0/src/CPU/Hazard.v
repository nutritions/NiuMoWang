module Hazard(
    input [4:0]rf_ra0_ex,
    input [4:0]rf_ra1_ex,
    input rf_re0_ex,
    input rf_re1_ex,
    input [4:0]rf_wa_mem,
    input rf_we_mem,
    input [1:0]rf_wd_sel_mem,
    input [31:0]alu_ans_mem,
    input [31:0]pc_add4_mem,
    input [31:0]imm_mem,
    input [4:0]rf_wa_wb,
    input rf_we_wb,
    input [31:0]rf_wd_wb,
    input [1:0]pc_sel_ex,
    input jal_id,
    output reg rf_rd0_fe,
    output reg rf_rd1_fe,
    output reg [31:0]rf_rd0_fd,
    output reg [31:0]rf_rd1_fd,
    output reg stall_if,
    output reg stall_id,
    output reg stall_ex,
    output reg flush_if,
    output reg flush_id,
    output reg flush_ex,
    output reg flush_mem
);

//数据冒险-前递


        //在内存访问阶段（MEM）进行写操作，执行阶段（EX）进行读操作，
        //并且执行阶段需要读取的寄存器与内存阶段写入的寄存器相同,并非数据存储器读取结果
        //或者写回阶段（WB）进行写操作，执行阶段(EX)进行读操作，
        //并且执行阶段需要读取的寄存器与写回阶段写入的寄存器相同


//0
    always@(*) 
    begin
        if((rf_we_mem & rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10))
        begin
            rf_rd0_fe = 1'b1;
            case(rf_wd_sel_mem)
                2'b00: begin
                    rf_rd0_fd = alu_ans_mem;
                end
                2'b01: begin
                    rf_rd0_fd = pc_add4_mem;
                end
                2'b11: begin
                    rf_rd0_fd = imm_mem;
                end
                default: rf_rd0_fd = 32'h0;
            endcase
        end
        else if(rf_we_wb & rf_re0_ex & (rf_ra0_ex == rf_wa_wb))
        begin
            rf_rd0_fe = 1'b1;
            rf_rd0_fd = rf_wd_wb;
        end
        else
            rf_rd0_fe = 1'b0;
    end

//1
    always@(*) 
    begin
        if((rf_we_mem & rf_re1_ex & (rf_ra1_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10))
        begin
            rf_rd1_fe = 1'b1;
            case(rf_wd_sel_mem)
                2'b00: begin
                    rf_rd1_fd = alu_ans_mem;
                end
                2'b01: begin
                    rf_rd1_fd = pc_add4_mem;
                end
                2'b11: begin
                    rf_rd1_fd = imm_mem;
                end
                default: rf_rd1_fd = 32'h0;
            endcase
        end
        else if(rf_we_wb & rf_re1_ex & (rf_ra1_ex == rf_wa_wb))
        begin
            rf_rd1_fe = 1'b1;
            rf_rd1_fd = rf_wd_wb;
        end
        else
            rf_rd1_fe = 1'b0;
    end



//数据冒险-冒泡
// 这种冒险的判断方式前三步与上一小节相同，但最后一个条件为 MEM 段的写回数据
// 选择为数据存储器的结果

//stall_if、id、ex，flush_mem
    always@(*)
    begin
        
        if(rf_we_mem & ((rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) | (rf_re1_ex & (rf_ra1_ex == rf_wa_mem))) & (rf_wd_sel_mem == 2'b10))
        begin
            stall_if = 1'b1;
            stall_id = 1'b1;
            stall_ex = 1'b1;
            flush_mem = 1'b1;
        end
        else begin
            stall_if = 1'b0;
            stall_id = 1'b0;
            stall_ex = 1'b0;
            flush_mem = 1'b0;
        end
    end


//控制冒险


//flush_id
    always@(*)
    begin
        if(((pc_sel_ex == 2'b01) | (pc_sel_ex == 2'b11)) | (jal_id == 1'b1))
            flush_id = 1'b1;
        else 
            flush_id = 1'b0;
    end

//flush_ex
    always@(*)
    begin
        if((pc_sel_ex == 2'b01) | (pc_sel_ex == 2'b11))
            flush_ex = 1'b1;
        else 
            flush_ex = 1'b0;
    end


endmodule
