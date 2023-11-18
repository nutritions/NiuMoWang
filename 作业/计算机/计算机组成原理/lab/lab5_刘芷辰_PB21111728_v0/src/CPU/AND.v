module AND(
    input [31:0]rhs,
    output [31:0]res
);

    wire [31:0]lhs = 32'hfffffffe;
    assign res = rhs & lhs;

endmodule