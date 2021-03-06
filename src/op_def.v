`ifndef OP_DEF_H
`define OP_DEF_H

`include "config.v"

// Transfer operations

`define ALU_OP_THA_WORD		(`ALU_OPCODE_SIZE'b0100_0000)
`define ALU_OP_THB_WORD		(`ALU_OPCODE_SIZE'b1000_0000)
`define ALU_OP_THA_HALF		(`ALU_OPCODE_SIZE'hxx)
`define ALU_OP_THB_HALF		(`ALU_OPCODE_SIZE'hxx)
`define ALU_OP_THA_BYTE		(`ALU_OPCODE_SIZE'hxx)
`define ALU_OP_THB_BYTE		(`ALU_OPCODE_SIZE'hxx)

`define ALU_OP_SWAP_WORD	(`ALU_OPCODE_SIZE'b1000_0001)
`define ALU_OP_SWAP_HALF	(`ALU_OPCODE_SIZE'hxx)
`define ALU_OP_SWAP_BYTE	(`ALU_OPCODE_SIZE'hxx)

// Arighmetic operations
`define ALU_OP_ADD		(`ALU_OPCODE_SIZE'b1000_0010)
`define ALU_OP_SUB		(`ALU_OPCODE_SIZE'b1000_0011)
`define ALU_OP_MUL		(`ALU_OPCODE_SIZE'b1000_0100)
`define ALU_OP_DIV		(`ALU_OPCODE_SIZE'b1000_0101)
`define ALU_OP_MOD		(`ALU_OPCODE_SIZE'b1000_0110)
`define ALU_OP_CMP		(`ALU_OPCODE_SIZE'b1000_0111)
`define ALU_OP_CGT		(`ALU_OPCODE_SIZE'b1000_1000)
`define ALU_OP_CGE		(`ALU_OPCODE_SIZE'b1000_1001)

// Logical operations
`define ALU_OP_AND		(`ALU_OPCODE_SIZE'b1000_1010)
`define ALU_OP_ORR		(`ALU_OPCODE_SIZE'b1000_1011)
`define ALU_OP_XOR		(`ALU_OPCODE_SIZE'b1000_1100)
`define ALU_OP_TST		(`ALU_OPCODE_SIZE'b1000_1101)
`define ALU_OP_NOT		(`ALU_OPCODE_SIZE'hxx)

// Shift operations
`define ALU_OP_SHL		(`ALU_OPCODE_SIZE'b1100_0000)
`define ALU_OP_SHR		(`ALU_OPCODE_SIZE'b1100_0001)
`define ALU_OP_SAR		(`ALU_OPCODE_SIZE'b1100_0010)
`define ALU_OP_ROL		(`ALU_OPCODE_SIZE'b1100_0011)
`define ALU_OP_ROR		(`ALU_OPCODE_SIZE'b1100_0100)

// System operations
`define ALU_OP_NOP		(`ALU_OPCODE_SIZE'hFF)

`endif // OP_DEF_H
