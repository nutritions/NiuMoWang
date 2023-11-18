module ADD(
    input [31:0] lhs,
    input [31:0] rhs,
    output reg [31:0] res
    );
    always@(*) begin
        res = lhs + rhs;
    end
endmodule
