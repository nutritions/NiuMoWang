module MUX1(
    input [31:0]src0,
    input [31:0]src1,
    input sel,
    output reg [31:0]res
);

    always@(*)
    begin
        if(sel)
            res = src1;
        else
            res = src0;
    end

endmodule