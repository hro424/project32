module PC (
	input clk,
	input rst,
	input `WORD in,
	output `WORD out);

always @(posedge clk, posedge rst) begin
	if (rst) begin
		pc <= 0;
	end
	else begin
	end
end

endmodule
