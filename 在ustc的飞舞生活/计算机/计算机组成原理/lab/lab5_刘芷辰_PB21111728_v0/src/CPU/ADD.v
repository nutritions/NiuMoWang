module ADD(
    input [31:0]rhs,
    output [31:0]res
);

    assign res = rhs + 32'h4;

endmodule