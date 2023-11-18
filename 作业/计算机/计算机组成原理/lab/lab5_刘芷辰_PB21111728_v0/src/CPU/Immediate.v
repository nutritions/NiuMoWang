module Immediate(
    input [31:0]inst,
    input [2:0]imm_type,
    output reg [31:0]imm
);

    always@(*)
    begin
        case(imm_type)
            3'b001:     //i-type
                imm = {{20{inst[31]}},inst[31:20]};
            3'b010:     //b-type
                imm = {{20{inst[31]}},inst[7],inst[30:25],inst[11:8],1'b0};
            3'b011:     //s-type
                imm = {{20{inst[31]}},inst[31:25],inst[11:7]};
            3'b100:     //j-type
                imm = {{12{inst[31]}},inst[19:12],inst[20],inst[30:21],1'b0};
            3'b101:     //u-type
                imm = {inst[31:12],12'h0};
            default:    //r-type
                imm = 32'h0000;
        endcase
    end

endmodule