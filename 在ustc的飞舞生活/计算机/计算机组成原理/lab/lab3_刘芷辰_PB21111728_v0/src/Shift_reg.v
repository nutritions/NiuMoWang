`timescale 1ns / 1ps

module Shift_reg(
    input rst,
    input clk,          // Work at 100MHz clock

    input [31:0] din,   // Data input  
    input [3:0] hex,    // Hexadecimal code for the switches
    input add,          // Add signal
    input del,          // Delete signal
    input set,          // Set signal
    
    output reg [31:0] dout  // Data output
);

    reg [31:0] shift_reg;  


    always @(posedge clk or posedge rst) begin
        if (rst) begin
            shift_reg <= 32'b0; 
            dout <= 32'b0;      
        end
        // Set
        else if (set) begin
                shift_reg <= din;  
            end
        // Add 
        else if (add) begin
                shift_reg <= {shift_reg[27:0], hex}; 
            end
        // Delete 
        else if (del) begin
                shift_reg <= {4'b0,shift_reg[31:4]};  
            end

            dout <= shift_reg[31:0];  
        end
    

endmodule


