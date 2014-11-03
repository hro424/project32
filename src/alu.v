`ifndef P32_ALU_V
`define P32_ALU_V

`include "config.v"
`include "op_def.v"

module ALU (
	input	`ALU_OPCODE	com,
	input	`WORD		in0,
	input	`WORD		in1,
	output	`WORD		out/*,
	output			flag_c,
	output			flag_s,
	output			flag_z
	*/
);

reg c, s, z;

assign out = alu(com, in0, in1);
/*
assign flag_c = c;
assign flag_s = s;
assign flag_z = z;
*/

function `WORD alu;
	input	`ALU_OPCODE	com;
	input	`WORD		a, b;

	case (com)
		`ALU_OP_THA_WORD: alu = a;
		`ALU_OP_THB_WORD: alu = b;
		`ALU_OP_THA_HALF: alu = a;
		`ALU_OP_THB_HALF: alu = b;
		`ALU_OP_THA_BYTE: alu = a;
		`ALU_OP_THB_BYTE: alu = b;
		`ALU_OP_ADD: begin
			alu = a + b;
		end
		`ALU_OP_SUB: begin
			alu = a - b;
		end
		`ALU_OP_MUL: begin
			alu = a * b;
		end
		`ALU_OP_DIV: begin
			alu = a / b;
		end
		`ALU_OP_MOD: begin
			alu = a % b;
		end
		`ALU_OP_CMP:
			if (a == b) begin
				c = 0;
				s = 0;
				z = 1;
			end
			else begin
				c = 0;
				s = 0;
				z = 0;
			end
		`ALU_OP_CGE:
			if (a >= b) begin
				c = 1;
				s = 0;
				z = 1;
			end
			else begin
				c = 0;
				s = 1;
				z = 0;
			end
		`ALU_OP_CGT: 
			if (a > b) begin
				c = 1;
				s = 0;
				z = 0;
			end
			else begin
				c = 0;
				s = 1;
				z = 1;
			end
		`ALU_OP_AND: alu = a & b;
		`ALU_OP_ORR: alu = a | b;
		`ALU_OP_XOR: alu = a ^ b;
		`ALU_OP_NOT: alu = ~a;
		`ALU_OP_SHL: begin
			alu = a << b;
		end
		`ALU_OP_SHR: begin
			alu = a >> b;
		end
		default: alu = `WORD_SIZE'hx;
	endcase
endfunction

endmodule

`endif // P32_ALU_V
