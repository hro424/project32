`include "config.v" 

module RegisterFile(
	input			clk,
	input			rst,
	input			wen_a,
	input			rd_a,
	input	`REGADDR	addr_a,
	input	`WORD		din_a,
	output	`WORD		dout_a,
	input			wen_b,
	input			rd_b,
	input	`REGADDR	addr_b,
	input	`WORD		din_b,
	output	`WORD		dout_b
);

reg	`WORD	mem[0:`REGADDR_MSB];

always @(posedge clk, posedge rst) begin
	if (rst) begin
		reset_mem();
	end
	else begin
		if (wen_a) begin
			mem[addr_a] <= din_a;
		end

		if (rd_a) begin
			dout_a <= mem[addr_a];
		end
		else begin
			dout_a <= HI_Z;
		end

		if (web_b) begin
			mem[addr_b] <= din_b;
		end

		if (rd_b) begin
			dout_b <= mem[addr_b];
		end
		else begin
			dout_b <= HI_Z;
		end
	end
end

function `REGADDR reset_mem

	for (i = 0; i < `NUM_REGS; i = i + 1) begin
		mem[i] = `WORD_SIZE'h0;
	end
	reset_mem = mem0;
endfunction

endmodule
