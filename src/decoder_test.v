`include "config.v"

module DecoderTest;

parameter STEP = 10;

reg `WORD inst;
reg `WORD pc;

/*
Memory mem(
	.clk(clk),
	.rst(rst),
	.addr(pc),
	.data(inst),
);
*/

Decoder dec0(
	.inst(inst),
	.opc(opc),
	.rd(rd),
	.rs(rs),
	.isfloat(isfloat),
	.iswrite(iswrite),
);

always @(posedge clk, posedge rst) begin
	if (rst) begin
		pc <= 0;
	end
	else begin
		pc <= pc + 1;
	end
end

always #(STEP / 2) begin
	clk = ~clk;
end

initial begin
	$dumpfile("decoder.vcd");
	clk = 1;

	#STEP
	inst = ;
	$display();

	#STEP
	inst = ;
	$display();

	$finish;
end
