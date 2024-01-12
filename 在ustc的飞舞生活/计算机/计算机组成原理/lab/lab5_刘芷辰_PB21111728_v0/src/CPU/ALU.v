`timescale 1ns / 1ps

module ALU(
    input [31:0] alu_src1, alu_src2,     //两操作数
    input [3:0] alu_func,           //操作功能
    output [31:0] alu_ans       //运算结果
    );
    reg [31:0] res;
    assign alu_ans = res;
    always@(*)
    case(alu_func)
        4'b0000:
        begin
            res = alu_src1 + alu_src2;
        end
        4'b0001:
        begin
            res = alu_src1 - alu_src2;
        end
        4'b0010:
        begin
            if(alu_src1 == alu_src2)
                res = 1;
            else
                res = 0;
        end
        4'b0011:
        begin
            if(alu_src1 < alu_src2)
                res = 1;
            else
                res = 0;
        end
        4'b0100:
        begin
            if($signed(alu_src1) < $signed(alu_src2))
                res = 1;
            else
                res = 0;
        end
        4'b0101:
        begin
            res = alu_src1 & alu_src2;
        end
        4'b0110:
        begin
            res = alu_src1 | alu_src2;
        end
        4'b0111:
        begin
            res = alu_src1 ^ alu_src2;
        end
        4'b1000:
        begin
            res = alu_src1 >> alu_src2;
        end
        4'b1001:
        begin
            res = alu_src1 << alu_src2;
        end
        default:
        begin
            res = 0;
        end
    endcase
endmodule







