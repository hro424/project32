module Glue


ALU alu_0(.clk(clk), .rst(rst), .in0(reg0), .in1(sel0), 
	.com(com), .out(sel1));

Register reg_0(.clk(clk), .rst(rst), .addr0( ), .din( ), .dout( ),
	.addr1( ), .din1( ), .dout1( ));

endmodule
