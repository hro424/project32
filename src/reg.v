`include "config.v" 
// 32-bit x 16 registers
// dual port
module RegisterFile(
	input			clk,
	input			rst,
	input			wen_a,
	input	`REGADDR	addr_a,
	input	`WORD		din_a,
	output	`WORD		dout_a,
	input			wen_b,
	input	`REGADDR	addr_b,
	input	`WORD		din_b,
	output	`WORD		dout_b
);

reg	`WORD	mem[0:`REGADDR_MSB];
integer i;

assign dout_a = mem[addr_a];
assign dout_b = mem[addr_b];

always @(posedge clk, posedge rst) begin
	if (rst) begin
		for (i = 0; i < `NUM_REGS; i = i + 1) begin
			mem[i] = `WORD_SIZE'h0;
		end
	end
	else begin
		if (wen_a) begin
			mem[addr_a] <= din_a;
		end

		if (wen_b) begin
			mem[addr_b] <= din_b;
		end
	end
end


endmodule
