`ifndef OP_DEF_H
`define OP_DEF_H

`include "config.v"

`define ALU_OP_THA		(`ALU_OP_SIZE'h0)
`define ALU_OP_THB		(`ALU_OP_SIZE'h1)
`define ALU_OP_ADD		(`ALU_OP_SIZE'h2)
`define ALU_OP_SUB		(`ALU_OP_SIZE'h3)
`define ALU_OP_MUL		(`ALU_OP_SIZE'h4)
`define ALU_OP_DIV		(`ALU_OP_SIZE'h5)
`define ALU_OP_AND		(`ALU_OP_SIZE'h6)
`define ALU_OP_ORR		(`ALU_OP_SIZE'h7)
`define ALU_OP_XOR		(`ALU_OP_SIZE'h8)

// system operations
`define OP_NOP			(`OPCODE_SIZE'h0)

// transfer operations
`define OP_MOV_REG_REG		(`OPCODE_SIZE'h10)
`define OP_MOV_REG_MEM		(`OPCODE_SIZE'h11)
`define OP_MOV_MEM_REG		(`OPCODE_SIZE'h12)

// arithmetic operations
`define OP_ADD_REG		(`OPCODE_SIZE'h21)
`define OP_ADD_IMM		(`OPCODE_SIZE'h22)
`define OP_SUB_REG		(`OPCODE_SIZE'h23)
`define OP_SUB_IMM		(`OPCODE_SIZE'h24)
`define OP_MUL_REG		(`OPCODE_SIZE'h25)
`define OP_DIV_REG		(`OPCODE_SIZE'h26)

// logical operations
`define OP_AND_REG		(`OPCODE_SIZE'h31)
`define OP_AND_IMM		(`OPCODE_SIZE'h32)
`define OP_ORR_REG		(`OPCODE_SIZE'h33)
`define OP_ORR_IMM		(`OPCODE_SIZE'h34)
`define OP_XOR_REG		(`OPCODE_SIZE'h35)
`define OP_XOR_IMM		(`OPCODE_SIZE'h36)
`define OP_NOT			(`OPCODE_SIZE'h37)
`define OP_TST_REG		(`OPCODE_SIZE'h38)
`define OP_TST_IMM		(`OPCODE_SIZE'h39)

// shift operations
`define OP_SHL_REG		(`OPCODE_SIZE'h41)
`define OP_SHL_IMM		(`OPCODE_SIZE'h42)
`define OP_SHR_REG		(`OPCODE_SIZE'h43)
`define OP_SHR_IMM		(`OPCODE_SIZE'h44)
`define OP_SAR_REG		(`OPCODE_SIZE'h45)
`define OP_SAR_IMM		(`OPCODE_SIZE'h46)
`define OP_ROR_REG		(`OPCODE_SIZE'h47)
`define OP_ROR_IMM		(`OPCODE_SIZE'h48)
`define OP_ROL_REG		(`OPCODE_SIZE'h49)
`define OP_ROL_IMM		(`OPCODE_SIZE'h4a)

// branch operations
`define OP_CMP_REG		(`OPCODE_SIZE'h51)
`define OP_CMP_IMM		(`OPCODE_SIZE'h52)
`define OP_BEQ			(`OPCODE_SIZE'h53)
`define OP_BNE			(`OPCODE_SIZE'h54)
`define OP_BGE			(`OPCODE_SIZE'h55)
`define OP_BLE			(`OPCODE_SIZE'h56)
`define OP_BGT			(`OPCODE_SIZE'h57)
`define OP_BLT			(`OPCODE_SIZE'h58)
`define OP_JMP			(`OPCODE_SIZE'h59)
`define OP_JSR			(`OPCODE_SIZE'h5a)
`define OP_RET			(`OPCODE_SIZE'h5b)

`endif // OP_DEF_H
