`ifndef P32_DEST_SEL_V
`define P32_DEST_SEL_V

module DestSelector(
	input [1:0] sel,
	input `WORD din,
	output `WORD dout0,
	output `WORD dout1,
	output `WORD dout2
);

assign dout0 = sel[0] ? din : 'hx;
assign dout1 = sel[0] ? 'hx : sel[1] ? din : 'hx;
assign dout2 = sel[0] ? 'hx : sel[1] ? 'hx : din;

endmodule

`endif // P32_DEST_SEL_V
