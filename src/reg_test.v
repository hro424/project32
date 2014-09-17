`include "config.v"

module RegisterFileTest;

parameter STEP = 10;

reg clk;
reg rst;
reg `WORD din_a;
reg `WORD din_b;
wire `WORD dout_a;
wire `WORD dout_b;
reg `REGADDR addr_a;
reg `REGADDR addr_b;
reg wen_a, wen_b;

RegisterFile rf0(.clk(clk), .rst(rst),
	.wen_a(wen_a), .addr_a(addr_a), .din_a(din_a), .dout_a(dout_a),
	.wen_b(wen_b), .addr_b(addr_b), .din_b(din_b), .dout_b(dout_b));

always #(STEP / 2) begin
	clk = ~clk;
end

initial begin
	$dumpfile("reg.vcd");
	clk = 1;

	#STEP
	wen_a = 1;
	addr_a = `REGADDR_SIZE'h0;
	din_a = `WORD_SIZE'hABCDEF00;
	$display("dout_a: %h  dout_b: %h", dout_a, dout_b);

	#STEP
	wen_a = 0;
	addr_a = `REGADDR_SIZE'h0;
	addr_b = `REGADDR_SIZE'h0;
	$display("dout_a: %h  dout_b: %h", dout_a, dout_b);

	#STEP
	wen_a = 1;
	addr_a = `REGADDR_SIZE'h0;
	din_a = `WORD_SIZE'hABCDEF01;
	addr_b = `REGADDR_SIZE'h0;
	$display("dout_a: %h  dout_b: %h", dout_a, dout_b);

	#STEP
	rst = 1;
	$display("dout_a: %h  dout_b: %h", dout_a, dout_b);

	#STEP
	$display("dout_a: %h  dout_b: %h", dout_a, dout_b);

	$finish;
end	

endmodule
