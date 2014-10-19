`ifndef OP_DEF_H
`define OP_DEF_H

`include "config.v"

// Transfer operations
`define ALU_OP_THA_WORD		(`ALU_OPCODE_SIZE'h00)
`define ALU_OP_THB_WORD		(`ALU_OPCODE_SIZE'h10)
`define ALU_OP_THA_HALF		(`ALU_OPCODE_SIZE'h20)
`define ALU_OP_THB_HALF		(`ALU_OPCODE_SIZE'h30)
`define ALU_OP_THA_BYTE		(`ALU_OPCODE_SIZE'h40)
`define ALU_OP_THB_BYTE		(`ALU_OPCODE_SIZE'h50)

`define ALU_OP_SWAP_WORD	(`ALU_OPCODE_SIZE'h60)
`define ALU_OP_SWAP_HALF	(`ALU_OPCODE_SIZE'h70)
`define ALU_OP_SWAP_BYTE	(`ALU_OPCODE_SIZE'h80)

// Arighmetic operations
`define ALU_OP_ADD		(`ALU_OPCODE_SIZE'h90)
`define ALU_OP_SUB		(`ALU_OPCODE_SIZE'h91)
`define ALU_OP_MUL		(`ALU_OPCODE_SIZE'h92)
`define ALU_OP_DIV		(`ALU_OPCODE_SIZE'h93)
`define ALU_OP_MOD		('ALU_OPCODE_SIZE'h94)
`define ALU_OP_CMP		(`ALU_OPCODE_SIZE'h95)
`define ALU_OP_CGT		(`ALU_OPCODE_SIZE'h96)
`define ALU_OP_CGE		(`ALU_OPCODE_SIZE'h97)

// Logical operations
`define ALU_OP_AND		(`ALU_OPCODE_SIZE'h91)
`define ALU_OP_ORR		(`ALU_OPCODE_SIZE'h92)
`define ALU_OP_XOR		(`ALU_OPCODE_SIZE'h93)
`define ALU_OP_NOT		(`ALU_OPCODE_SIZE'h94)

// Shift operations
`define ALU_OP_SHL		(`ALU_OPCODE_SIZE'h95)
`define ALU_OP_SHR		(`ALU_OPCODE_SIZE'h96)
`define ALU_OP_SAR		(`ALU_OPCODE_SIZE'h97)
`define ALU_OP_ROL		(`ALU_OPCODE_SIZE'h98)
`define ALU_OP_ROR		(`ALU_OPCODE_SIZE'h99)

// System operations
`define ALU_OP_NOP		(`ALU_OPCODE_SIZE'hFF)

`endif // OP_DEF_H
