`ifndef P32_REG_V
`define P32_REG_V

`include "config.v" 
// 32-bit x 16 registers
// dual port
module RegisterFile(
	input			clk,
	input			rst,
	input	`REGADDR	addr0,
	input	`WORD		din0,
	input			we0,
	output	`WORD		dout0,
	input	`REGADDR	addr1,
	input	`WORD		din1,
	input			we1,
	output	`WORD		dout1
);

reg	`WORD	mem[0:`NUM_REGS - 1];
integer i;

assign dout0 = mem[addr0];
assign dout1 = mem[addr1];

always @(posedge clk, posedge rst) begin
	if (rst) begin
		for (i = 0; i < `NUM_REGS; i = i + 1) begin
			mem[i] = `WORD_SIZE'h0;
		end
	end
	else begin
		$display(" R0:%h  R1:%h  R2:%h  R3:%h",
			mem[0], mem[1], mem[2], mem[3]);
		$display(" R4:%h  R5:%h  R6:%h  R7:%h",
			mem[4], mem[5], mem[6], mem[7]);
		$display(" R8:%h  R9:%h R10:%h R11:%h",
			mem[8], mem[9], mem[10], mem[11]);
		$display("R12:%h R13:%h R14:%h R15:%h",
			mem[12], mem[13], mem[14], mem[15]);
		if (we0) begin
			mem[addr0] <= din0;
		end

		if (we1) begin
			mem[addr1] <= din1;
		end
	end
end

endmodule
`endif // P32_REG_V
