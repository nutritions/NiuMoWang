module RF(
    input clk,
    input we,
    input [4:0]ra0,
    input [4:0]ra1,
    input [4:0]wa,
    input [4:0]ra_dbg,
    input [31:0]wd,
    output reg [31:0]rd0,
    output reg [31:0]rd1,
    output reg [31:0]rd_dbg
);

    reg [31:0] regfile[0:31];

    always@(posedge clk) 
    begin
        if(we)
        begin
            if(wa)
                regfile[wa] <= wd;
        end
    end

    always@(*)
    begin
        if(ra0 == 5'h0)
            rd0 <= 32'h0;
        else if(we & (ra0 == wa))
            rd0 <= wd;
        else
            rd0 <= regfile[ra0];
    end

    always@(*)
    begin
        if(ra1 == 5'h0)
            rd1 <= 32'h0;
        else if(we & (ra1 == wa))
            rd1 <= wd;
        else
            rd1 <= regfile[ra1];
    end

    always@(*)
    begin
        if(ra_dbg == 5'h0)
            rd_dbg <= 32'h0;
        else if(we & (ra_dbg == wa))
            rd_dbg <= wd;
        else
            rd_dbg <= regfile[ra_dbg];
    end

    integer i;
    initial 
    begin
        i = 0;
        while (i < 32) 
        begin
            regfile[i] = 32'b0;
            i = i + 1;
        end
            regfile [2] = 32'h2ffc;
            regfile [3] = 32'h1800;
    end

endmodule