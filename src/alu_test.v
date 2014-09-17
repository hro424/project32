`include "config.v"
`include "op_def.v"

module ALUTest(
);

parameter STEP = 10;

reg	`OPCODE	com;
//reg	[(16 - 1):0]  com;
reg	`WORD	a, b;
wire	`WORD	y;

ALU alu0(.com(com), .a(a), .b(b), .y(y));

initial begin
	$dumpfile("alu.vcd");

	com <= `OP_ADD_REG;
	a <= `WORD_SIZE'ha5a5;
	b <= `WORD_SIZE'h5a5a;
	#STEP
	$display("com:%b a:%b b:%b y:%b", com, a, b, y);
	$finish;
end

endmodule
