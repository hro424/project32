module Fetcher(
	input clk,
	input rst,
	input `WORD addr,
	output `WORD pc
);

reg `WORD counter = 0;

always @(posedge clk, posedge rst) begin
	if (rst) begin
		counter <= 0;
	end
	else begin
		if (addr) begin
			counter = addr;
		end
		else begin
			counter = counter + 1;
		end
		pc = counter;
	end
end

endmodule
