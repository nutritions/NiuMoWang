module Branch(
    input [31:0]op1,
    input [31:0]op2,
    input [2:0]br_type,
    output reg br
);

    always@(*)
    begin
        case(br_type)
            3'b001: begin           //blt
                if($signed(op1) < $signed(op2))
                    br = 1;
                else
                    br = 0;
            end
            3'b010: begin           //beq
                if(op1 == op2)
                    br = 1;
                else
                    br = 0;
            end
            3'b011: begin           //
                if(op1 != op2)
                    br = 1;
                else
                    br = 0;
            end
            3'b100: begin       //bge
                if($signed(op1) >= $signed(op2))
                    br = 1;
                else
                    br = 0;
            end
            3'b101: begin       //bltu
                if(op1 < op2)
                    br = 1;
                else
                    br = 0;
            end
            3'b110: begin
                if(op1 >= op2)//bgeu
                    br = 1;
                else
                    br = 0;
            end
            default: br = 0;
        endcase
    end

endmodule