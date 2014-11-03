`include "proc.v"

module Test;

`define DEPTH 65536
parameter STEP = 10;

reg clk;
reg rst;

wire `WORD addr0;
wire `WORD addr1;
wire `WORD dout;
wire we;

reg `WORD memory [0:`DEPTH - 1];

always #(STEP / 2) begin
	clk <= ~clk;
end

Processor proc(
	.clk(clk),
	.rst(rst),
	.pc(addr0),
	.inst(memory[addr0]),
	.mem_addr(addr1),
	.mem_in(memory[addr1]),
	.mem_out(dout),
	.we(we)
);

initial begin
	$dumpfile("test.vcd");
	$dumpvars(0, Test);
	$readmemh("mem.dat", memory);
	clk <= 0;
	rst <= 1;

	#(STEP *  1 / 4)
	#STEP

	rst <= 0;

	#(STEP * 100)
	$finish;
end

always @(posedge clk) begin
	if (we) memory[addr1] <= dout;
end

always @(negedge clk) begin
	$display("pc: %h data: %b ", proc.counter, proc.inst);
end

endmodule
