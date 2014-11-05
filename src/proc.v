`ifndef PC32_PROC_V
`define PC32_PROC_V

`include "config.v"
`include "alu.v"
`include "decoder.v"
`include "dst_sel.v"
`include "src_sel.v"
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
	else if (clk) begin
		if (sel_dst == 2'b00 &&
		    (op_lsb[2:0] == 3'b000 ||
		     op_lsb[2:0] == {cflag, sflag, zflag})) begin
			counter <= dst2;
		end
		else begin
			counter <= counter + 1;
		end
	end
end

wire `ALU_OPCODE	opcode;
wire `WORD		operand0;
wire `WORD		operand1;
wire `WORD		aluout;
wire `WORD		dst0;	// to reg
wire			dst0_we;
wire `WORD		rf_in0;
wire			rf_we0;
wire `WORD		dst2;	// to pc
wire `REGADDR		rd;
wire `REGADDR		rs;
wire			isfloat;
wire			iswrite;
wire [1:0]		sel_dst;
wire			sel_src;
wire `HALF		imm;
wire `WORD		rfout1;
wire 			cflag;
wire 			sflag;
wire 			zflag;
wire [3:0] op_msb;
wire [3:0] op_lsb;

assign opcode = {op_msb, (op_msb == 4'b0100) ? 0 : op_lsb};

ALU alu(
	.rst(rst),
	.clk(clk),
	.com(opcode),
	.in0(operand0),
	.in1(operand1),
	.out(aluout),
	.carry(cflag),
	.sign(sflag),
	.zero(zflag)
);

DestSelector dselector(
	.sel(sel_dst),
	.din(aluout),
	.dout0(dst0),
	.we0(dst0_we),
	.dout1(mem_addr),
	.dout2(dst2)
);

assign operand1 = sel_src ? imm : rfout1;
assign rf_in0 =
	(sel_dst == 2'b10 && opcode == `ALU_OP_THB_WORD) ? mem_in : dst0;
assign rf_we0 =
	(sel_dst == 2'b10 && opcode == `ALU_OP_THB_WORD) ? 1'b1 : dst0_we;

RegisterFile rf(
	.clk(clk),
	.rst(rst),
	.addr0(rd),
	.din0(rf_in0),
	.dout0(operand0),
	.we0(rf_we0),
	.addr1(rs),
	.din1('h0),
	.we1('h0),
	.dout1(rfout1)
);

Decoder dec(
	.inst(inst),
	.opcode({op_msb, op_lsb}),
	.rd(rd),
	.rs(rs),
	.isfloat(isfloat),
	.src(sel_src),
	.dst(sel_dst),
	.imm(imm)
);

assign pc = counter;
assign mem_out = operand1;
assign we = (sel_dst == 2'b10 && opcode == `ALU_OP_THA_WORD) ? 1'b1 : 1'b0;

endmodule

`endif // PC32_PROC_V
