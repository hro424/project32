`ifndef PC32_PROC_V
`define PC32_PROC_V

`include "config.v"
`include "alu.v"
`include "decoder.v"
`include "DestSelector.v"
`include "SrcSelector.v"
`include "reg.v"

module Processor(
	input	clk,
	input	rst,
	output	`WORD pc,	// program counter
	input	`WORD inst,	// instruction
	output	`WORD mem_addr,	// memory address
	input	`WORD mem_in,	// input from memory
	output	`WORD mem_out,	// output to memory
	output	we		// write enable
);

reg `WORD counter;

always @(posedge clk, posedge rst) begin
	if (rst) begin
		counter <= 0;
	end
	else begin
		counter <= counter + 1;
	end
end

wire `ALU_OPCODE	opcode;
wire `WORD	operand0;
wire `WORD	operand1;
wire `WORD	aluout;
wire `WORD	dst0;
wire `WORD	dst2;
wire `REGADDR	rd;
wire `REGADDR	rs;
wire		isfloat;
wire		iswrite;
wire [1:0]	sel_dst;
wire		sel_src;
wire `HALF	imm;
wire `WORD	rfout1;

ALU alu(
	.com(opcode),
	.in0(operand0),
	.in1(operand1),
	.out(aluout)
);

DestSelector dselector(
	.sel(sel_dst),
	.din(aluout),
	.dout0(dst0),
	.dout1(mem_addr),
	.dout2(dst2)
);

assign operand1 = sel_src ? imm : rfout1;

RegisterFile rf(
	.clk(clk),
	.rst(rst),
	.addr0(rd),
	.din0(dst0),
	.dout0(operand0),
	.addr1(rs),
	.din1(mem_in),
	.dout1(rfout1)
);

Decoder dec(
	.inst(inst),
	.opcode(opcode),
	.rd(rd),
	.rs(rs),
	.isfloat(isfloat),
	.iswrite(iswrite),
	.dst(sel_dst),
	.src(sel_src),
	.imm(imm)
);

assign pc = counter;
assign mem_out = operand1;
assign we = iswrite;

endmodule

`endif // PC32_PROC_V
