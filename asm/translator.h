#ifndef P32_ASM_TRANSLATOR_H
#define P32_ASM_TRANSLATOR_H

#include <string>
#include <list>

namespace p32_asm {

struct translator
{
    static const uint32_t OP_TYPE0 =    0x00000000;
    static const uint32_t OP_TYPE1_1 =  0x80000000;
    static const uint32_t OP_TYPE1_2 =  0xC0000000;
    static const uint32_t OP_TYPE2 =    0x40000000;
    static const uint32_t OP_TYPE_REG_REF = 0x10000000;
    static const uint32_t OP_TYPE_REF_REG = 0x20000000;

    static const uint32_t FN_FLOAT =    0x08000000;
    static const uint32_t FN_IMM =      0x04000000;
    static const uint32_t FN_SEL_PC =   0x00000000;
    static const uint32_t FN_SEL_REG1 = 0x01000000;
    static const uint32_t FN_SEL_SRC =  0x02000000;
    static const uint32_t FN_SEL_REG2 = 0x03000000;

    static const uint32_t DEST_SHIFT = 20;
    static const uint32_t SRC_SHIFT = 16;

    virtual void encode(std::list<uint32_t>& out,
                        const std::string& opc, const std::string& opr1,
                        const std::string& opr2) = 0;

    uint16_t to_uint16(const std::string& imm)
    {
        unsigned long n = stoul(imm, 0, 0);
        return static_cast<uint16_t>(n & 0xFFFF);
    }

    // from literal to register address
    uint8_t to_reg(const std::string& opr)
    {
        return regaddr.at(opr);
    }

    virtual uint32_t to_dest(const std::string& opr)
    {
        return to_reg(opr) << DEST_SHIFT;
    }

    virtual uint32_t to_src(const std::string& opr)
    {
        return to_reg(opr) << SRC_SHIFT;
    }

    static const std::map<std::string, uint8_t> regaddr;
};

// opc rd, rs
// opc rd, imm
struct type1_op : public translator
{
    virtual void encode(std::list<uint32_t>& out,
                        const std::string& opc, const std::string& opr1,
                        const std::string& opr2) = 0;
    static const std::map<std::string, uint32_t> name2code;
};

// opc rd
struct type2_op : public translator
{
    virtual void encode(std::list<uint32_t>& out,
                        const std::string& opc, const std::string& opr1,
                        const std::string& opr2 = "") = 0;
    static const std::map<std::string, uint32_t> name2code;
};


bool is_immediate(const std::string& opr)
{
    return isdigit(opr[0]);
}

static const std::regex re_reg("^r[([0-9])(1[0-5])]$");
static const std::regex re_ref("^@r[([0-9])(1[0-5])]$");
static const std::regex re_refoff("^@\(r[([0-9])(1[0-5])]$");

bool is_register(const std::string& opr)
{
    return std::regex_match(opr, re_reg);
}

bool is_reference(const std::string& opr)
{
    return std::regex_match(opr, re_ref);
}

bool is_reference_offset(const std::string& opr)
{
    return std::regex_match(opr, re_refoff);
}

bool is_label(const std::string& opr)
{
    return !is_immediate(opr) && !is_register(opr) && !is_reference(opr);
}


} // namespace p32_asm

#endif // P32_ASM_TRANSLATOR_H
