module Decoder(
	input `WORD inst,
	output `ALU_OPCODE opcode,
	output `REGADDR rd,
	output `REGADDR rs,
	output isfloat,
	output iswrite,
	output [1:0] dst,
	output src,
	output `HALF imm,
	output we
);

assign rd = inst[27:24];
assign rs = inst[23:20];
assign isfloat = inst[19];
assign src = inst[18];
assign dst = inst[17:16];
assign iswrite = &dst;
assign imm = inst[15:0];

wire op_msb = inst[31:28];
wire op_lsb = op_msb > 8 && src ? inst[rs] : inst[15:12];
assign opcode = {op_msb, op_lsb};

endmodule
