module Glue

reg `WORD	pc;

ALU alu_0(.clk(clk), .rst(rst), .in0(reg0), .in1(sel0), 
	.com(com), .out(sel1));

RegisterFile reg0(
	.clk(clk),
	.rst(rst),
	.addr0( ),
	.din( ),
	.dout( ),
	.addr1( ),
	.din1( ),
	.dout1( )
);

Memory mem0(
	.clk(clk),
	.rst(rst),
	.addr0(),
	.din0(),
	.dout0(),
	.addr1(),
	.din1(),
	.dout1(),
};

Decoder dec0(
	.inst(inst),
	.opc(opc),
	.rd(rd),
	.rs(rs),
	.isfloat(isfloat),
	.iswrite(iswrite),
	.dst(dst),
	.src(src),
	,imm(imm),
};

always @(posedge clk, posedge rst) begin
	if (rst) begin
		pc <= 0;
	end
	else begin
		inst <= mem_out;
		pc += 4;
		mem_addr <= pc;
	end
end

endmodule
