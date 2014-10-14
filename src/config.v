`ifndef CONFIG_H
`define CONFIG_H

`default_nettype		none

`define BYTE_SIZE		8
`define BYTE_MSB		(`BYTE_SIZE - 1)
`define BYTE			[`BYTE_MSB:0]
`define HALF_SIZE		16
`define HALF_MSB		(`HALF_SIZE - 1)
`define HALF			[`HALF_MSB:0]
`define WORD_SIZE		32
`define WORD_MSB		(`WORD_SIZE - 1)
`define WORD			[`WORD_MSB:0]
`define ALU_OPCODE_SIZE		4
`define ALU_OPCODE_MSB		(`ALU_OPCODE_SIZE - 1)
`define ALU_OPCODE		[`ALU_OPCODE_MSB:0]

`define HI_Z			(`WORD_SIZE'hz)
`define UNDEF			(`WORD_SIZE'hx)

`define REGADDR_SIZE		4
`define REGADDR_MSB		(`REGADDR_SIZE - 1)
`define REGADDR			[`REGADDR_MSB:0]
`define NUM_REGS		(1 << `REGADDR_SIZE)

`endif // CONFIG_H
