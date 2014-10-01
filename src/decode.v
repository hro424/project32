module Decoder(
	input `WORD inst,
	output `BYTE opc,
	output `BYTE rd,
	output `BYTE rs,
	output isfloat,
	output iswrite,
	output [1:0] dst,
	output src,
	output `HALF imm,
);

assign opc = inst[31:28];
assign rd = inst[27:24];
assign rs = inst[23:20];
assign isfloat = inst[19];
assign src = inst[18]
assign dst = inst[17:16];
assign imm = inst[15:0];
assign we = &dst;

endmodule
