`include "config.v"
`include "op_def.v"

module ALU (
	input	`ALU_OPCODE	com,
	input	`WORD		in0,
	input	`WORD		in1,
	output	`WORD		out
);

assign out = alu(com, in0, in1);

function `WORD alu;
	input	`ALU_OPCODE	com;
	input	`WORD		a, b;

	case (com)
		`ALU_OP_THA_WORD: alu = a;
		`ALU_OP_THB_WORD: alu = b;
		`ALU_OP_ADD: alu = a + b;
		`ALU_OP_SUB: alu = a - b;
		`ALU_OP_MUL: alu = a * b;
		`ALU_OP_AND: alu = a & b;
		`ALU_OP_ORR: alu = a | b;
		`ALU_OP_XOR: alu = a ^ b;
		default: alu = `WORD_SIZE'hx;
	endcase
endfunction

endmodule
