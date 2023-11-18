`timescale 1ns / 1ps

module Branch(
	input [31:0] op1,op2,
	input [1:0] br_type,
	output reg br
    );
    always @(*) begin
    	case (br_type)
			// beq
			2'b10:  br = (op1 == op2) ? 1 : 0;

			//blt
			2'b01:
    		if (op1[31] == op2[31]) begin
    			if (op1[30:0] < op2[30:0])
    				br = 1;
    			else
    				br = 0;
			end
   	    	else if ( op1[31] == 1 ) br = 1;
   	    	else br = 0;

			default: br = 0;
		endcase
    end
endmodule
