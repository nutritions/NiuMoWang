module ALU #(parameter WIDTH = 32) (
  input [WIDTH-1:0] alu_src1,
  input [WIDTH-1:0] alu_src2,
  input [3:0] alu_func,
  output [WIDTH-1:0] alu_ans,
  output of
);

  reg [WIDTH-1:0] alu_ans_reg; // 输出结果 alu_ans
  reg of_reg; // 溢出标志位寄存器

  always @(*) begin
    case (alu_func)
      // ADD
      4'b0000: begin    
        alu_ans_reg = alu_src1 + alu_src2;
        of_reg = (alu_src1[WIDTH-1] == alu_src2[WIDTH-1]) && (alu_ans_reg[WIDTH-1] != alu_src1[WIDTH-1]);
      end
      // SUB
      4'b0001: begin    
        alu_ans_reg = alu_src1 - alu_src2;
        of_reg = (alu_src1[WIDTH-1] != alu_src2[WIDTH-1]) && (alu_ans_reg[WIDTH-1] != alu_src1[WIDTH-1]);
      end
      // EQ
      4'b0010: begin alu_ans_reg = (alu_src1 == alu_src2) ? 1 : 0;  of_reg <= 0;    end 
      // LT_u           
      4'b0011: begin alu_ans_reg = (alu_src1 < alu_src2) ? 1 : 0;  of_reg <= 0; end 
      // LT_s
      4'b0100: begin alu_ans_reg = ($signed(alu_src1) < $signed(alu_src2)) ? 1 : 0;  of_reg <= 0;  end
      // AND
      4'b0101: begin alu_ans_reg = alu_src1 & alu_src2;     of_reg <= 0;  end         
      // OR            
      4'b0110: begin alu_ans_reg = alu_src1 | alu_src2;     of_reg <= 0;  end        
      // XOR         
      4'b0111: begin alu_ans_reg = alu_src1 ^ alu_src2;     of_reg <= 0;  end   
      // SHR             
      4'b1000: begin alu_ans_reg = alu_src1 >> alu_src2;    of_reg <= 0;  end          
      // SHL       
      4'b1001: begin alu_ans_reg = alu_src1 << alu_src2;    of_reg <= 0;  end
      // SRA
      4'b1010: begin alu_ans_reg = $signed(alu_src1) >>> alu_src2;    of_reg <= 0;  end
      // Default is 0           
      default: begin
         alu_ans_reg = 0; 
         of_reg = 0;   
      end                
    endcase
  end

  assign alu_ans = alu_ans_reg;
  //assign of = of_reg;

endmodule






