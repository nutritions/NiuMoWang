module Hazard(
    input [4:0]rf_ra0_ex,
    input [4:0]rf_ra1_ex,
    //它表示在执行阶段是否需要从寄存器堆中读取 rf_ra0_ex 所指示的寄存器的值
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

//forward

//rf_rd0_fe 是否要用前递的数据
    always@(*)
    begin
        //MEM段写使能为1，要用rf_ra0_ex所对应的寄存器，寄存器读的地址与MEM段的写地址一样
        //读取-使用冒险(Load-Use Hazard)，由于读取在 MEM 段结束才能完成,所以不能是lw（写回的数并非数据存储器读取结果）
        //WB段写使能为1，要用rf_ra0_ex所对应的寄存器，寄存器读的地址与WB段的写地址一样
        if(((rf_we_mem & rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10)) | (rf_we_wb & rf_re0_ex & (rf_ra0_ex == rf_wa_wb)))
            rf_rd0_fe = 1'b1;
        else
            rf_rd0_fe = 1'b0;
    end

//rf_rd1_fe
    always@(*)
    begin
        if(((rf_we_mem & rf_re1_ex & (rf_ra1_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10)) | (rf_we_wb & rf_re1_ex & (rf_ra1_ex == rf_wa_wb)))
            rf_rd1_fe = 1'b1;
        else
            rf_rd1_fe = 1'b0;
    end

//rf_rd0_fd
//要前递的数据，是本条指令的ALU在EX或MEM阶段的结果
    always@(*) 
    begin
        //rf_wd_sel_mem
        if((rf_we_mem & rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10))
        begin
            case(rf_wd_sel_mem)
                //add addi auipc sll
                2'b00: begin
                    rf_rd0_fd = alu_ans_mem;
                end
                //jal jalr
                2'b01: begin
                    rf_rd0_fd = pc_add4_mem;
                end
                //lui
                2'b11: begin
                    rf_rd0_fd = imm_mem;
                end
                default: rf_rd0_fd = 32'h0;
            endcase
        end
        else if(rf_we_wb & rf_re0_ex & (rf_ra0_ex == rf_wa_wb))
        begin
            rf_rd0_fd = rf_wd_wb;
        end
    end

//rf_rd1_fd
    always@(*) 
    begin
        if((rf_we_mem & rf_re1_ex & (rf_ra1_ex == rf_wa_mem)) & (rf_wd_sel_mem != 2'b10))
        begin
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
            rf_rd1_fd = rf_wd_wb;
        end
    end



//bubble
//判断的时机是EX和MEM段间，把IF/ID、ID/EX以及IF前的准备工作也stall
//stall_if
//而还未执行的 IF 前(PC)
    always@(*)
    begin
        //MEM段写使能为1，要用rf_ra0/1_ex所对应的寄存器，寄存器读的地址与MEM段的写地址一样，lw指令
        if(rf_we_mem & ((rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) | (rf_re1_ex & (rf_ra1_ex == rf_wa_mem))) & (rf_wd_sel_mem == 2'b10))
            stall_if = 1'b1;
        else 
            stall_if = 1'b0;
    end
//而还未执行的 IF/ID段中的指令需要停驻一个周期
//stall_id
    always@(*)
    begin
        if(rf_we_mem & ((rf_re0_ex & (rf_ra0_ex == rf_wa_mem )) | (rf_re1_ex & (rf_ra1_ex == rf_wa_mem))) & (rf_wd_sel_mem == 2'b10))
            stall_id = 1'b1;
        else 
            stall_id = 1'b0;
    end
//而还未执行的ID/EX 段中的指令需要停驻一个周期
//stall_ex
    always@(*)
    begin
        if(rf_we_mem & ((rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) | (rf_re1_ex & (rf_ra1_ex == rf_wa_mem))) & (rf_wd_sel_mem == 2'b10))
            stall_ex = 1'b1;
        else 
            stall_ex = 1'b0;
    end

//flush_mem
    always@(*)
    begin
        if(rf_we_mem & ((rf_re0_ex & (rf_ra0_ex == rf_wa_mem)) | (rf_re1_ex & (rf_ra1_ex == rf_wa_mem))) & (rf_wd_sel_mem == 2'b10))
            flush_mem = 1'b1;
        else 
            flush_mem = 1'b0;
    end

//control
//flush_id
//清空IF/ID段寄存器
    always@(*)
    begin
        //jalr,br,jal 
        if(((pc_sel_ex == 2'b01) | (pc_sel_ex == 2'b11)) | (jal_id == 1'b1))
            flush_id = 1'b1;
        else 
            flush_id = 1'b0;
    end

//flush_ex
//清空ID/EX段寄存器
    always@(*)
    begin
        //jalr,br
        if((pc_sel_ex == 2'b01) | (pc_sel_ex == 2'b11))
            flush_ex = 1'b1;
        else 
            flush_ex = 1'b0;
    end


endmodule