module NPC_SEL(
    input [31:0]pc_add4_if,
    input [31:0]pc_jalr_ex,
    input [31:0]alu_ans_ex,
    input [31:0]jal_pc,
    input [1:0]pc_sel_ex,
    input jal_id,
    output reg [31:0]pc_next
);

    always@(*)
    begin
        if(pc_sel_ex == 2'b01)  //jalr
            pc_next = pc_jalr_ex;
        else if(pc_sel_ex == 2'b11)     //br
            pc_next = alu_ans_ex;
        else if(jal_id)
            pc_next = jal_pc;
        else
            pc_next = pc_add4_if;
    end

endmodule