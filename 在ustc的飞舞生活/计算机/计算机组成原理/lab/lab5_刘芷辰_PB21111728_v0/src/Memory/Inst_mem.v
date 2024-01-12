module Inst_mem(
    input [31:0]im_addr,
    output [31:0]im_dout
);

    inst_mem inst_mem(
        .a(im_addr[9:2]),
        .spo(im_dout)
    );

endmodule