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

// Clock generator
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

	#(STEP * 16)
	$finish;
end

always @(posedge clk) begin
	if (we) memory[addr1] <= dout;
end

always @(negedge clk) begin
	$display("\n[%h] code:%b(%hh)", proc.counter, proc.inst, proc.inst);
	$display("  DEC>  op:%b(%b:%b) rd:%d rs:%d sel_src:%b sel_dst:%b we:%b",
		 proc.opcode, proc.op_msb, proc.op_lsb, proc.rd, proc.rs,
		 proc.sel_src, proc.sel_dst, proc.we);
	$display("  SSEL> rfout:%hh", proc.rfout1);
	$display("  ALU>  in0:%hh in1:%hh out:%hh(%dd)",
		 proc.operand0, proc.operand1, proc.aluout, proc.aluout);
	$display("  DSEL> reg:%hh mem:%hh pc:%hh",
		 proc.dst0, proc.mem_addr, proc.dst2);
	$display("  FLAG> carry:%b sign:%b zero:%b",
		 proc.cflag, proc.sflag, proc.zflag);
	$display("  MEM> addr:%h read:%h write:%h",
		proc.mem_addr, proc.mem_in, proc.mem_out);
end

endmodule
