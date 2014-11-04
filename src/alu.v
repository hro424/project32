`ifndef P32_ALU_V
`define P32_ALU_V

`include "config.v"
`include "op_def.v"

module ALU (
	input			rst,
	input			clk,
	input	`ALU_OPCODE	com,
	input	`WORD		in0,
	input	`WORD		in1,
	output	`WORD		out,
	output			carry,
	output			sign,
	output			zero
);

reg c, s, z;

assign out = alu(com, in0, in1);
assign carry = c;
assign sign = s;
assign zero = z;

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
	`ALU_OP_ADD: alu = a + b;
	`ALU_OP_SUB: alu = a - b;
	`ALU_OP_MUL: alu = a * b;
	`ALU_OP_DIV: alu = a / b;
	`ALU_OP_MOD: alu = a % b;
	`ALU_OP_CMP: alu = a;
	`ALU_OP_CGE: alu = a;
	`ALU_OP_CGT: alu = a;
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

always @(posedge clk, posedge rst) begin
	if (rst) begin
		c <= 0;
		s <= 0;
		z <= 0;
	end
	else begin
		case(com)
		`ALU_OP_CMP:
			if (in0 == in1) begin
				c <= 0;
				s <= 0;
				z <= 1;
			end
			else begin
				c <= 1;
				s <= 1;
				z <= 0;
			end
		`ALU_OP_CGE:
			if (in0 >= in1) begin
				c <= 1;
				s <= 0;
				z <= 1;
			end
			else begin
				c <= 0;
				s <= 1;
				z <= 0;
			end
		`ALU_OP_CGT: 
			if (in0 > in1) begin
				c <= 1;
				s <= 0;
				z <= 0;
			end
			else begin
				c <= 0;
				s <= 1;
				z <= 1;
			end
		endcase
	end
end

endmodule

`endif // P32_ALU_V
