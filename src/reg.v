`include "config.v" 
// 32-bit x 16 registers
// dual port
module RegisterFile(
	input			clk,
	input			rst,
	input	`REGADDR	addr0,
	input	`WORD		din0,
	output	`WORD		dout0,
	input	`REGADDR	addr1,
	input	`WORD		din1,
	output	`WORD		dout1
);

reg	`WORD	mem[0:`REGADDR_MSB];
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
		if (din0 != 'hx) begin
			mem[addr0] <= din0;
		end

		if (din1 != 'hx) begin
			mem[addr1] <= din1;
		end
	end
end

endmodule
