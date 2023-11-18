module Data_mem(
    input clk,
    input dm_we,
    input [31:0]dm_addr,
    input [31:0]dm_din,
    input [31:0]mem_check_addr,
    output [31:0]dm_dout,
    output [31:0]mem_check_data
);

    data_mem data_mem(
        .a(dm_addr[9:2]),
        .d(dm_din),
        .dpra(mem_check_addr[7:0]),
        .clk(clk),
        .we(dm_we),
        .spo(dm_dout),
        .dpo(mem_check_data)
    );

endmodule