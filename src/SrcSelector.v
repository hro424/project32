module SrcSelector(
	input sel,
	input `WORD din0,
	input `WORD din1,
	output `WORD dout
);

assign dout = sel ? din1 : din0;

endmodule
