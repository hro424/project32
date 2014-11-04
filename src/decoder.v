`ifndef P32_DECODER_V
`define P32_DECODER_V

module Decoder(
	input `WORD inst,
	output `ALU_OPCODE opcode,
	output `REGADDR rd,
	output `REGADDR rs,
	output isfloat,
	output src,
	output [1:0] dst,
	output `HALF imm
);

assign isfloat = inst[27];
assign src = inst[26];
assign dst = inst[25:24];
assign rd = inst[23:20];
assign rs = inst[19:16];
assign imm = inst[15:0];

wire [3:0] op_msb = inst[31:28];
wire [3:0] op_lsb = src ? inst[19:16] : inst[15:12];

assign opcode = {op_msb, op_lsb};

endmodule

`endif // P32_DECODER_V
