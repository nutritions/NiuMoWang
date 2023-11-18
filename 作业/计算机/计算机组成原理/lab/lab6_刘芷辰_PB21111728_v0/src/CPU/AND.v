module AND(
    input [31:0]rhs,
    input [31:0]lhs,
    output [31:0]res
);

    assign res = rhs & lhs;

endmodule