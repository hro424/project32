`include "config.v"

module RegisterFileTest;

parameter STEP = 10;

reg clk;
reg `WORD din_a;
reg `WORD din_b;
reg `WORD dout_a;
reg `WORD dout_b;
reg `REGADDR addr_a;
reg `REGADDR addr_b;

wire wen_a, rd_a, web_b, rd_b;

RegisterFile rf0(.clk(clk), .rst(rst),
	.wen_a(wen_a), .rd_a(rd_a), .addr_a(addr_a),
	.din_a(din_a), .dout_a(dout_a),
	.wen_b(wen_b), .rd_b(rd_b), .addr_b(addr_b),
	.din_b(din_b), .dout_b(dout_b));

always #(STEP / 2) begin
	clk = ~clk;
end

initial begin
	$dumpfile("reg.vcd");
	clk = 1;

	#STEP
	wen_a <= 1;
	rd_a <= 0;
	addr_a <= `REGADDR_SIZE'h0;
	din_a <= `WORD_SIZE'hABCDEF00;

	#STEP
	wen_a = 0;
	rd_a = 1;
	addr_a = `REGADDR_SIZE'h0;
	$display("dout: %h", dout_a);

	#STEP
	$display("dout: %h", dout_a);

	$finish;
end	

endmodule
