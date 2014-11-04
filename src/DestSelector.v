`ifndef P32_DEST_SEL_V
`define P32_DEST_SEL_V

module DestSelector(
	input [1:0] sel,
	input `WORD din,
	output `WORD dout0,
	output we0,
	output `WORD dout1,
	output `WORD dout2
);

// reg (01 or 11)
assign dout0 = sel[0] ? din : 'hx;
assign we0 = sel[0] ? 1 : 0;

// mem (10)
assign dout1 = sel[0] ? 'hx : sel[1] ? din : 'hx;

// pc (00)
assign dout2 = sel[0] ? 'hx : sel[1] ? 'hx : din;

endmodule

`endif // P32_DEST_SEL_V
