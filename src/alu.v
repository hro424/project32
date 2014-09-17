`include "config.v"
`include "op_def.v"

module ALU (
	input	`OPCODE	com,
	input	`WORD	a,
	input	`WORD	b,
	output	`WORD	y
);

assign y = alu(com, a, b);

function `WORD alu;
	input	`OPCODE	com;
	input	`WORD	a, b;

	case (com)
		`OP_NOP: alu = a;
		`OP_MOV_REG_REG: alu = b;
		`OP_ADD_REG: alu = a + b;
		`OP_SUB_REG: alu = a - b;
		`OP_MUL_REG: alu = a * b;
		`OP_AND_REG: alu = a & b;
		`OP_ORR_REG: alu = a | b;
		`OP_XOR_REG: alu = a ^ b;
		default: alu = `WORD_SIZE'hx;
	endcase
endfunction

endmodule
