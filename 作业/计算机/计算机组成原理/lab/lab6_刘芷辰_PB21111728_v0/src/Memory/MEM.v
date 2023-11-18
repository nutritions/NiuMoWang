module MEM(
    input clk,

    // MEM Data BUS with CPU
	// IM port
    input [31:0] im_addr,
    output [31:0] im_dout,
	
	// DM port
    input  [31:0] dm_addr,
    input dm_we,
    input  [31:0] dm_din,
    output [31:0] dm_dout,

    // MEM Debug BUS
    input [31:0] mem_check_addr,
    output [31:0] mem_check_data
);

//IM
    Inst_mem IM(
       .a(im_addr[9:2]),
       .spo(im_dout)
    );

//DM
    Data_mem DM(
        .a(dm_addr[9:2]),
     .d(dm_din),
     .dpra(mem_check_addr),
     .clk(clk),
     .we(dm_we),  
     .spo(dm_dout),    
     .dpo(mem_check_data)  
    );

endmodule
