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
    static const uint32_t FN_FLOAT =    0x08000000;
    static const uint32_t FN_IMM =      0x04000000;
    static const uint32_t FN_SEL_PC =   0x00000000;
    static const uint32_t FN_SEL_REG1 = 0x01000000;
    static const uint32_t FN_SEL_SRC =  0x02000000;
    static const uint32_t FN_SEL_REG2 = 0x03000000;

    translator();
    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2) = 0;

    bool is_immediate(const std::string& opr);
    bool is_register(const std::string& opr);
    uint16_t to_uint16(const std::string& imm);
    uint8_t to_reg(const std::string& opr);

    map<std::string, uint8_t> regaddr;
};

translator::translator()
{
    //TODO: build a table of hashcode of registers
    regaddr['r0'] = 0;
    regaddr['r1'] = 1;
    regaddr['r2'] = 2;
    regaddr['r3'] = 3;
    regaddr['r4'] = 4;
    regaddr['r5'] = 5;
    regaddr['r6'] = 6;
    regaddr['r7'] = 7;
    regaddr['r8'] = 8;
    regaddr['r9'] = 9;
    regaddr['r10'] = 10;
    regaddr['r11'] = 11;
    regaddr['r12'] = 12;
    regaddr['r13'] = 13;
    regaddr['r14'] = 14;
    regaddr['r15'] = 15;
}

bool
translator::is_immediate(const std::string& opr)
{
    return is_number(opr);
}

bool
translator::is_register(const std::string& opr)
{
    // TODO: use hash code
    re = regex("^r[([0-9])(1[0-5])]$");
    return regex_match(opr, re);
}

uint16_t
translator::to_uint16(const std::string& imm)
{
    uint16_t n = to_number(imm);
    return n & 0xFFFF;
}

uint16_t
translator::to_reg(const std::string& opr)
{
    //TODO: use hash code
    re = regex("^r[([0-9])(1[0-5])]$");
    if (regex_match(opr, re)) {
        return regaddr[i];
    }
    return 0xffff;
}

struct mov_translator : public translator
{
    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2);
};

struct branch_translator : public translator
{
    virtual uint32_t encode(const std::string& opc, const std::string& opr1,
                            const std::string& opr2);
};

#define DEST(op, opr)               \
    if (is_register(opr)) {         \
        code |= to_dest(opr) | op;  \
    } else                          \
        code = 0;                   \
    }

uint32_t
branch_translator::encode(std::string& opc, std::string& opr1,
                         std::string& opr2)
{
    uint32_t code = TYPE0;

    if (opc.length() == 0 || opr1.length() == 0 || opr2.length() > 0) {
        // syntax error
        return 0;
    }

    if (opc == "jmp") {
        if (is_immediate(opr1)) {
            code |= IMM | to_uint16(opr1);
        }
        else (is_register(opr1)) {
            code |= to_dest(opr1);
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
    arith_translator();
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

arith_translator::arith_translator()
{
    str2code['add'] = 0;
    str2code['sub'] = 1;
    str2code['mul'] = 2;
    str2code['div'] = 3;
    str2code['mod'] = 4;
    str2code['cmp'] = 5;
    stf2code['cgt'] = 6;
    str2code['cge'] = 7;
    str2code['and'] = 8;
    str2code['orr'] = 9;
    str2code['xor'] = 10;
    str2code['not'] = 11;
    str2code['tst'] = 12;
}

uint32_t
arith_translator::enc_op(std::string& op, size_t shift)
{
    uint32_t code = str2code[op];
    // hashtable
    return code << shift;
}

uint32_t
arith_translator::encode(std::string& op, std::string& opr1 std::string& opr2)
{
    uint32_t code = TYPE2;

    if (!is_register(opr1)) {
        // syntax error
        return 0;
    }

    code |= to_reg(opr1) << DEST_SHIFT;

    if (is_immediate(opr2)) {
        code |= FN_IMMEDIATE | FN_SEL_REG1 | to_uint16(opr2);
        code |= enc_op(op, 16);
    }
    else if (is_register(opr2)) {
        code |= FN_SEL_REG1 | (to_reg(opr2) << SRC_SHIFT);
        code |= enc_op(op, 12);
    }
    else {
        code = 0;
    }
    return code;
}

struct SwapTranslator : public translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

} // namespace

std::map<std::string, uint32_t> symbols;
std::map<std::string, translator> translator;

int
translate(std::string& opc, std::string& opr1, std::string& opr2)
{
    translator[opc].encode(opr1, opr2);
}

init()
{
    ts['mov'] = std::move(mov_translator);
    ts['swap'] = ;
    ts['jmp'] = ;
    ts['beq'] = ;
    ts['bne'] = ;
    ts['bge'] = ;
    ts['ble'] = ;
    ts['bgt'] = ;
    ts['blt'] = ;
    ts['add'] = ;
    ts['sub'] = ;
    ts['mul'] = ;
    ts['div'] = ;
    ts['mod'] = ;
    ts['cmp'] = ;
    ts['cgt'] = ;
    ts['cge'] = ;
    ts['and'] = ;
    ts['orr'] = ;
    ts['xor'] = ;
    ts['not'] = ;
    ts['tst'] = ;
    ts['shl'] = ;
    ts['shr'] = ;
    ts['sar'] = ;
    ts['rol'] = ;
    ts['ror'] = ;
    ts['nop'] = ;
}
    

int
main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    std::string line;
    std::regex re("^[ \\t]*(?:([\\w\\.]+)[ \\t]*:)?[ \\t]*(?:(\\w+)[ \\t]+(@?\\w+)[ \\t]*(?:,[ \\t]*(@?\\w+))?)?.*");
    std::cmatch cm;
    uint32_t offset = 0;

    while (getline(ifs, line)) {
        //std::string str = remove_comment(line);
        //std::cout << str << std::endl;
        if (std::regex_match(line.c_str(), cm, re)) {
            std::cout << "--- match ---" << std::endl;
            if (cm[1].length() > 0) {
                std::cout << "label:\t\t'" << cm[1] << "'" << std::endl;
                symbols[cm[1].str()] = offset + 4;
            }

            if (cm[2].length() > 0) {
                std::cout << "opcode:\t\t'" << cm[2] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[3] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[4] << "'" << std::endl;
                encoder[opcode_str].encode(operand1_str, operand2_str);
                offset += 4;
            }
        }
    }

    std::cout << "symbols:" << std::endl;
    for (auto i : symbols) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}

