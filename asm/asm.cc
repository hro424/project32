#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

namespace {
struct translator
{
    static const uint32_t OP_TYPE0 =    0x00000000;
    static const uint32_t OP_TYPE1 =    0x10000000;
    static const uint32_t OP_TYPE2 =    0x80000000;
    static const uint32_t OP_TYPE3 =    0xC0000000;
    static const uint32_t FN_FLOAT =    0x08000000;
    static const uint32_t FN_IMM =      0x04000000;
    static const uint32_t FN_SEL_PC =   0x00000000;
    static const uint32_t FN_SEL_REG1 = 0x01000000;
    static const uint32_t FN_SEL_SRC =  0x02000000;
    static const uint32_t FN_SEL_REG2 = 0x03000000;

    static const uint32_t DEST_SHIFT = 20;
    static const uint32_t SRC_SHIFT = 16;

    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2) = 0;

    static bool is_immediate(const std::string& opr)
    {
        return isdigit(opr[0]);
    }

    static bool is_register(const std::string& opr)
    {
        return std::regex_match(opr, re_reg);
    }

    static bool is_reference(const std::string& opr)
    {
        return std::regex_match(opr, re_ref);
    }

    static bool is_reference_offset(const std::string& opr)
    {
        return std::regex_match(opr, re_refoff);
    }

    static uint16_t to_uint16(const std::string& imm)
    {
        unsigned long n = stoul(imm, 0, 0);
        return static_cast<uint16_t>(n & 0xFFFF);
    }

    // from literal to register address
    static uint8_t to_reg(const std::string& opr)
    {
        return regaddr.at(opr);
    }

    static uint32_t to_dest(const std::string& opr)
    {
        return to_reg(opr) << DEST_SHIFT;
    }

    static uint32_t to_src(const std::string& opr)
    {
        return to_reg(opr) << SRC_SHIFT;
    }

    static const std::map<std::string, uint8_t> regaddr;
    static const std::regex re_reg;
    static const std::regex re_ref;
    static const std::regex re_refoff;
};

const std::map<std::string, uint8_t> translator::regaddr = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7},
    {"r8", 8},
    {"r9", 9},
    {"r10", 10},
    {"r11", 11},
    {"r12", 12},
    {"r13", 13},
    {"r14", 14},
    {"r15", 15}
};

const std::regex translator::re_reg("^r[([0-9])(1[0-5])]$");
const std::regex translator::re_ref("^@r[([0-9])(1[0-5])]$");
const std::regex translator::re_refoff("^@\(r[([0-9])(1[0-5])]$");

struct mov_translator : public translator
{
    static const uint32_t 
    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2);
};

uint32_t
mov_translator::encode(const std::string& opc, const std::string& opr1,
                       const std::string& opr2)
{
    if (opc == "mov") {
    }
    else if (opc == "swp") {
    }

    return 0;
}

struct branch_translator : public translator
{
    static const uint32_t BEQ = 0x80000;
    static const uint32_t BNE = 0x90000;
    static const uint32_t BGE = 0xa0000;
    static const uint32_t BLE = 0xb0000;
    static const uint32_t BGT = 0xc0000;
    static const uint32_t BLT = 0xd0000;

    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2);
};

#define DEST(OP, OPR)                   \
    do {                                \
        if (is_register(OPR)) {         \
            code |= to_dest(OPR) | OP;  \
        } else {                        \
            code = 0;                   \
        }                               \
    } while (false)

uint32_t
branch_translator::encode(const std::string& opc, const std::string& opr1,
                          const std::string& opr2) {
    uint32_t code = OP_TYPE0;

    if (opc.length() == 0 || opr1.length() == 0 || opr2.length() > 0) {
        // syntax error
        return 0;
    }

    if (opc == "jmp") {
        if (is_immediate(opr1)) {
            code |= FN_IMM | to_uint16(opr1);
        }
        else if (is_register(opr1)) {
            code |= to_dest(opr1);
        }
        else if (is_label(opr1)) {
            // TODO:
        }
        else {
            code = 0;
        }
    }
    else if (opc == "beq") {
        DEST(BEQ, opr1);
    }
    else if (opc == "bne") {
        DEST(BNE, opr1);
    }
    else if (opc == "bge") {
        DEST(BGE, opr1);
    }
    else if (opc == "ble") {
        DEST(BLE, opr1);
    }
    else if (opc == "bgt") {
        DEST(BGT, opr1);
    }
    else if (opc == "blt") {
        DEST(BLT, opr1);
    }
    else {
        // error
        code = 0;
    }
    return code;
}

// add, sub, mul, div, mod, cmp
struct arith_translator : public translator
{
    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2);

    uint32_t enc_op(const std::string& op, size_t shift)
    {
        return str2code.at(op) << shift;
    }

    static const std::map<std::string, uint8_t> str2code;
};

const std::map<std::string, uint8_t> arith_translator::str2code =
{
    {"add", 0},
    {"sub", 1},
    {"mul", 2},
    {"div", 3},
    {"mod", 4},
    {"cmp", 5},
    {"cgt", 6},
    {"cge", 7},
    {"and", 8},
    {"orr", 9},
    {"xor", 10},
    {"not", 11},
    {"tst", 12}
};

uint32_t
arith_translator::encode(const std::string& op, const std::string& opr1,
                         const std::string& opr2)
{
    if (!is_register(opr1)) {
        // syntax error
        return 0;
    }

    uint32_t code = OP_TYPE2 | to_dest(opr1);

    if (is_immediate(opr2)) {
        code |= FN_IMM | FN_SEL_REG1 | to_uint16(opr2);
        code |= enc_op(op, 16);
    }
    else if (is_register(opr2)) {
        code |= FN_SEL_REG1 | to_src(opr2);
        code |= enc_op(op, 12);
    }
    else {
        code = 0;
    }
    return code;
}

struct shift_translator : public translator
{
    virtual uint32_t encode(const std::string& op, const std::string& opr1,
                            const std::string& opr2);

    uint32_t enc_op(const std::string& op, size_t shift)
    {
        return str2code.at(op) << shift;
    }

    static const std::map<std::string, uint8_t> str2code;
};

const std::map<std::string, uint8_t> shift_translator::str2code = {
    {"shl", 0},
    {"shr", 1},
    {"sar", 2},
    {"rol", 3},
    {"ror", 4},
};

uint32_t
shift_translator::encode(const std::string& op, const std::string& opr1,
                         const std::string& opr2)
{
    if (!is_register(opr1)) {
        // syntax error
        return 0;
    }

    uint32_t code = OP_TYPE3 | to_dest(opr1);

    if (is_immediate(opr2)) {
        code |= FN_IMM | FN_SEL_REG1 | to_uint16(opr2);
        code |= enc_op(op, 16);
    }
    else if (is_register(opr2)) {
        code |= FN_SEL_REG1 | to_src(opr2);
        code |= enc_op(op, 12);
    }
    else {
        code = 0;
    }
    return code;
}

} // namespace

mov_translator mov_ts;
branch_translator br_ts;
arith_translator ar_ts;
shift_translator sh_ts;

std::map<std::string, uint32_t> strtab;

const std::map<std::string, translator*> ts = {
    {"mov", &mov_ts},
    {"swp", &mov_ts},
    {"jmp", &mov_ts},
    {"beq", &br_ts},
    {"bne", &br_ts},
    {"bge", &br_ts},
    {"ble", &br_ts},
    {"bgt", &br_ts},
    {"blt", &br_ts},
    {"add", &ar_ts},
    {"sub", &ar_ts},
    {"mul", &ar_ts},
    {"div", &ar_ts},
    {"mod", &ar_ts},
    {"cmp", &ar_ts},
    {"cgt", &ar_ts},
    {"cge", &ar_ts},
    {"and", &ar_ts},
    {"orr", &ar_ts},
    {"xor", &ar_ts},
    {"not", &ar_ts},
    {"tst", &ar_ts},
    {"shl", &sh_ts},
    {"shr", &sh_ts},
    {"sar", &sh_ts},
    {"rol", &sh_ts},
    {"ror", &sh_ts},
};

// opc rd, rs
// opc rd, imm
struct type1_op : public translator
{
    static const uint32_t OP_TYPE1_1 = 0x80000000;
    static const uint32_t OP_TYPE1_2 = 0xC0000000;

    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2) = 0;
    static const std::map<std::string, uint32_t> name2code;
};

const std::map<std::string, uint32_t> type1_op::name2code =
{
    {"mov", 0x00},
    {"swp", 0x01},
    {"add", 0x02},
    {"sub", 0x03},
    {"mul", 0x04},
    {"div", 0x05},
    {"mod", 0x06},
    {"cmp", 0x07},
    {"cgt", 0x08},
    {"cge", 0x09},
    {"and", 0x0A},
    {"orr", 0x0B},
    {"xor", 0x0C},
    {"tst", 0x0D},

    {"shl", 0x10},
    {"shr", 0x11},
    {"sar", 0x12},
    {"rol", 0x13},
    {"ror", 0x14},
};

// opc rd, rs
struct rd_rs : public type1_op
{
    uint32_t encode(const std::string& opc, const std::string& opr1,
                    const std::string& opr2)
    {
        uint32_t code = name2code[opc];

        if (code > 0xF) {
            code = OP_REG_REG_2 | ((code & 0xF) << 12);
        }
        else {
            code = OP_REG_REG_1 | (code << 12);
        }
        return code | to_dest(opr1) | to_src(opr2) | FN_SEL_REG1;
    }
};

// opc rd, imm
struct rd_imm : public type1_op
{
    uint32_t encode(const std::string& opc, const std::string& opr1,
                    const std::string& opr2)
    {
        uint32_t code = name2code[opc];

        if (code > 0xF) {
            code = OP_TYPE1_2 | ((code & 0xF) << 16);
        }
        else {
            code = OP_TYPE1_1 | (code << 16);
        }
        return code | to_dest(opr1) | to_uint16(opr2) | FN_IMM | FN_SEL_REG1;
    }
};

// mov rd, @rs
struct rd_ref : public mov_op
{
    uint32_t encode(const std::string& opc, const std::string& opr1,
                    const std::string& opr2)
    {
        return OP_REG_REF | to_dest(opr1) | to_src(opr2) | FN_SEL_SRC;
    }
};

// mov rd @(rs + imm)
struct rd_refoff : public mov_op
{
    uint32_t
    encode_rd_refoff(const std::string& opc, const std::string& opr1,
                     const std::string& opr2)
    {
        /*
        src = opr2;
        imm = opr2;

        return OP_TYPE_RREF | to_dets(opr1) | src | imm | FN_SEL_SRC;
        */
        return 0;
    }
}

uint32_t
encode_rd(const std::string& opc, const std::string& opr1)
{
    if (opc == "jmp") {
        fn = FN_SEL_PC;
    }

    return OP_TYPE_R | to_dest(opr1) | fn;
}

uint32_t
encode_imm(const std::string& opc, const std::string& opr1)
{
}

uint32_t
encode_label(const std::string& opc, const std::string& opr1)
{
}

uint32_t
encode_ref_rd(const std::string& opc, const std::string& opr1,
              const std::string& opr2)
{
    return OP_TYPE_REF_REG | to_dest(opr1) | to_src(opr2) | FN_SEL_REG1;
}

uint32_t
encode_refoff_rc(const std::string& opc, const std::string& opr1,
                 const std::string& opr2)
{
    return OP_TYPE_REF_REG | dest | to_src(opr2) | FN_SEL_REG1;
}

uint32_t
translate(const std::string& opc, const std::string& opr1,
          const std::string& opr2)
{
    if (translator::is_register(opr1)) {
        if (translator::is_register(opr2)) {
            encode_rd_rs(opc, opr1, opr2);
        }
        else if (translator::is_immediate(opr2)) {
            encode_rd_imm(opc, opr1, opr2);
        }
        else if (translator::is_reference(opr2)) {
            encode_rd_ref(opc, opr1, opr2);
        }
        else if (translator::is_reference_offset(opr2)) {
            encode_rd_refoff(opc, opr1, opr2);
        }
        else if (opr2.length() == 0) {
            encode_rd(opc, opr1);
        }
        else {
            // syntax error
        }
    }
    else if (translator::is_immediate(opr1)) {
        encode_imm(opc, opr1);
    }
    else if (translator::is_label(opr1)) {
        encode_label(opc, opr1);
    }
    else if (translator::is_reference(opr1)) {
        encode_ref_rd(opc, opr1, opr2);
    }
    else if (translator::is_reference_offset(opr1)) {
        encode_refoff_rd(opc, opr1, opr2);
    }

    return ts.at(opc)->encode(opc, opr1, opr2);
}

int
main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    std::string line;
    const std::regex re("^[ \\t]*(?:([\\w\\.]+)[ \\t]*:)?[ \\t]*(?:(\\w+)[ \\t]+(@?\\w+)[ \\t]*(?:,[ \\t]*(@?\\w+))?)?.*");
    std::cmatch cm;
    uint32_t offset = 0;

    while (getline(ifs, line)) {
        //std::string str = remove_comment(line);
        //std::cout << str << std::endl;
        if (std::regex_match(line.c_str(), cm, re)) {
            std::cout << "--- match ---" << std::endl;
            if (cm[1].length() > 0) {
                std::cout << "label:\t\t'" << cm[1] << "'" << std::endl;
                strtab[cm[1].str()] = offset + 4;
            }

            if (cm[2].length() > 0) {
                std::cout << "opcode:\t\t'" << cm[2] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[3] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[4] << "'" << std::endl;
                translate(cm[2], cm[3], cm[4]);
                offset += 4;
            }
        }
    }

    std::cout << "strtab:" << std::endl;
    for (auto i : strtab) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}

