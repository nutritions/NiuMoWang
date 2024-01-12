`timescale 1ns / 1ps

module CTRL(
    input [31:0] inst,
    output reg jal,
    output reg jalr,
    output reg [2:0] br_type,
    output reg rf_we,
    output reg [1:0] rf_wd_sel,
    output reg alu_src1_sel,
    output reg alu_src2_sel,
    output reg [3:0] alu_func,
    output reg [2:0]imm_type,
    output reg mem_we,
    output reg rf_re0,
    output reg rf_re1
    );
    always@(*) begin
        case(inst[6:0])
        //add
        7'b0110011: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b00;
            alu_src1_sel = 0;
            alu_src2_sel = 0;
            case(inst[14:12])
                3'b000: begin
                    if(inst[30] == 0) alu_func = 0; //add
                    else alu_func = 1; //sub
                        end
                3'b111: alu_func = 5; //and
                3'b110: alu_func = 6; //or
                3'b100: alu_func = 7; //xor
                3'b010: alu_func = 4; //slt
                3'b011: alu_func = 3; //sltu
                3'b001: alu_func = 9; //sll
                3'b101: begin
                    if(inst[30] == 0) alu_func = 8; //srl
                    else alu_func = 10; //sra
                        end
                default: alu_func = 15;
                endcase
            mem_we = 0;
            imm_type = 3'b000;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            if(inst[24:20] != 5'h0) rf_re1 = 1'b1;
            else rf_re1 = 1'b0;
        end


        //addi
        7'b0010011: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b00;
            alu_src1_sel = 0;
            alu_src2_sel = 1;
            case(inst[14:12])
                3'b000: alu_func = 0; //addi
                3'b111: alu_func = 5; //andi
                3'b110: alu_func = 6; //ori
                3'b100: alu_func = 7; //xori
                3'b010: alu_func = 4; //slti
                3'b011: alu_func = 3; //sltiu
                3'b001: alu_func = 9; //slli
                3'b101: begin
                        if(inst[30] == 0) alu_func = 8; //srli
                        else alu_func = 10; //srai
                        end
                default: alu_func = 15;
            endcase
            mem_we = 0;
            if((inst[14:12] == 3'b101) & (inst[31:25] == 7'b0100000))
                imm_type = 3'b110;
            else
                imm_type = 3'b001;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end
        //jalr
        7'b1100111: begin 
            jal = 0;
            jalr = 1;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b01;
            alu_src1_sel = 0;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 0;
            imm_type = 3'b001;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end
        //lw
        7'b0000011: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            if(inst[11:7] != 5'h0) rf_we = 1;
            rf_wd_sel = 2'b10;
            alu_src1_sel = 0;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 0;
            imm_type = 3'b001;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end


        //beq,blt
        7'b1100011: begin 
            jal = 0;
            jalr = 0;
            case(inst[14:12])
                3'b000: br_type = 2; //beq
                3'b100: br_type = 1; //blt
                3'b001: br_type = 3; //bne
                3'b101: br_type = 4; //bge
                3'b110: br_type = 5; //bltu
                3'b111: br_type = 6; //bgeu
                default:br_type = 0;
            endcase
            rf_we = 0;      
            rf_wd_sel = 2'b11;
            alu_src1_sel = 1;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 0;
            imm_type = 3'b010;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            if(inst[24:20] != 5'h0) rf_re1 = 1'b1;
            else rf_re1 = 1'b0;
        end


        //sw
        7'b0100011: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 0;
            rf_wd_sel = 2'b11;
            alu_src1_sel = 0;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 1;
            imm_type = 3'b011;
            if(inst[19:15] != 5'h0) rf_re0 = 1'b1;
            else rf_re0 = 1'b0;
            if(inst[24:20] != 5'h0) rf_re1 = 1'b1;
            else rf_re1 = 1'b0;
        end


        //lui
        7'b0110111: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b11;
            alu_src1_sel = 1;
            alu_src2_sel = 1;
            alu_func = 4'b1111;
            mem_we = 0;
            imm_type = 3'b101;
            rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end
        //auipc
        7'b0010111: begin 
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b00;
            alu_src1_sel = 1;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 0;
            imm_type = 3'b101;
            rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end


        //jal
        7'b1101111: begin 
            jal = 1;
            jalr = 0;
            br_type = 0;
            rf_we = 1;
            rf_wd_sel = 2'b01;
            alu_src1_sel = 1;
            alu_src2_sel = 1;
            alu_func = 0;
            mem_we = 0;
            imm_type = 3'b100;
            rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end
    
    
        default: begin
            jal = 0;
            jalr = 0;
            br_type = 0;
            rf_we = 0;
            rf_wd_sel = 2'b11;
            alu_src1_sel = 0;
            alu_src2_sel = 0;
            alu_func = 10;
            mem_we = 0;   
            imm_type = 3'b000;  
            rf_re0 = 1'b0;
            rf_re1 = 1'b0;
        end
        endcase
    end
endmodule