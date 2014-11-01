#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include "translator.h"

namespace p32_asm {

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

const std::map<std::string, uint32_t> type2_op::name2code =
{
    {"jmp", 0x00},
    {"beq", 0x01},
    {"bne", 0x02},
    {"bge", 0x03},
    {"ble", 0x04},
    {"bgt", 0x05},
    {"blt", 0x06},
};

// opc rd, rs
struct ttor_rd_rs : public type1_op
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2)
    {
        uint32_t code = name2code.at(opc);

        if (code > 0xF) {
            code = OP_TYPE1_2 | ((code & 0xF) << 12);
        }
        else {
            code = OP_TYPE1_1 | (code << 12);
        }
        out.push_back(code | to_dest(opr1) | to_src(opr2) | FN_SEL_REG1);
    }
};

// opc rd, imm
struct ttor_rd_imm : public type1_op
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2)
    {
        uint32_t code = name2code.at(opc);

        if (code > 0xF) {
            code = OP_TYPE1_2 | ((code & 0xF) << 16);
        }
        else {
            code = OP_TYPE1_1 | (code << 16);
        }
        out.push_back(code | to_dest(opr1) | to_uint16(opr2) |
                      FN_IMM | FN_SEL_REG1);
    }

    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                uint32_t opr2)
    {
        uint32_t code = name2code.at(opc);

        if (code > 0xF) {
            code = OP_TYPE1_2 | ((code & 0xF) << 16);
        }
        else {
            code = OP_TYPE1_1 | (code << 16);
        }
        out.push_back(code | to_dest(opr1) | (opr2 & 0xFFFF) |
                      FN_IMM | FN_SEL_REG1);
    }
};

// opc rd
// b, not
struct ttor_rd : public type2_op
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2 = "")
    {
        uint32_t fn = 0;

        if (opc == "jmp") {
            fn = FN_SEL_PC;
        }

        out.push_back(OP_TYPE2 | name2code.at(opc) | to_dest(opr1) | fn);
    }
};

// opc imm
// jmp, system
struct ttor_imm : public type2_op
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2 = "")
    {
        uint32_t fn;

        if (opc == "jmp") {
            fn = FN_SEL_PC;
            // TODO: cut off lsb
        }
        out.push_back(OP_TYPE2 | to_dest(opr1) | FN_IMM);
    }
};

// mov rd, @rs
struct ttor_rd_ref : public translator
{
    uint32_t to_src(const std::string& opr)
    {
        return to_reg(opr.substr(1, std::string::npos)) << SRC_SHIFT;
    }

    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2)
    {
        out.push_back(OP_TYPE_REG_REF | to_dest(opr1) | to_src(opr2) |
                      FN_SEL_SRC);
    }
};

// mov @rd, rs
struct ttor_ref_rs : public translator
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2)
    {
        out.push_back(OP_TYPE_REF_REG | to_dest(opr1) | to_src(opr2) |
                      FN_SEL_REG1);
    }
};

/*
// jmp label
struct ttor_label : public translator
{
    void encode(std::list<uint32_t>& out,
                const std::string& opc, const std::string& opr1,
                const std::string& opr2 = "")
    {
        // search label and get its address

    }
};

// mov rd @(rs + imm)
struct rd_refoff : public translate_rd_ref
{
    uint32_t to_src(const std::string& opr)
    {
        //return to_reg(opr.substr(2, std::string::nops)) << SRC_SHIFT;
    }

    uint16_t to_uint16(const std::string& opr)
    {
        return 0;
    }

    uint32_t
    encode_rd_refoff(const std::string& opc, const std::string& opr1,
                     const std::string& opr2)
    {
        return OP_REG_REF | to_dest(opr1) | to_src(opr2) | to_imm(opr2) |
            FN_SEL_SRC | FN_IMM;
    }
}
*/


/*
// mov @(rd + imm), rs
class translate_refoff_rs
{
    uint32_t encode(const std::string& opc, const std::string& opr1,
                    const std::string& opr2)
    {
        return OP_TYPE_REF_REG | dest | to_src(opr2) | FN_SEL_REG1;
    }
};
*/

} // namespace

std::map<std::string, uint32_t> strtbl;

p32_asm::ttor_rd_rs ts_rd_rs;
p32_asm::ttor_rd_imm ts_rd_imm;
p32_asm::ttor_rd_ref ts_rd_ref;
p32_asm::ttor_rd ts_rd;
p32_asm::ttor_imm ts_imm;
p32_asm::ttor_ref_rs ts_ref_rs;

bool
get_label_addr(const std::string& label, uint32_t& addr)
{
    std::map<std::string, uint32_t>::iterator it;

    std::cout << "resolving label '" << label << "'" << std::endl;
    it = strtbl.find(label);
    if (it != strtbl.end()) {
        addr = it->second;
        return true;
    }
    return false;
}

void
translate(const std::string& file_name, uint32_t line_num, std::ofstream& ofs,
          uint32_t current, const std::string& opc,
          const std::string& opr1, const std::string& opr2,
          const std::string& line)
{
    // Call translator by format
    std::list<uint32_t> code;

    if (p32_asm::is_register(opr1)) {
        if (opr2.length() == 0) {
            ts_rd.encode(code, opc, opr1);
        }
        else if (p32_asm::is_register(opr2)) {
            ts_rd_rs.encode(code, opc, opr1, opr2);
        }
        else if (p32_asm::is_immediate(opr2)) {
            ts_rd_imm.encode(code, opc, opr1, opr2);
        }
        else if (p32_asm::is_reference(opr2)) {
            ts_rd_ref.encode(code, opc, opr1, opr2);
        }
        /*
        else if (is_reference_offset(opr2)) {
            rd_refoff.encode(opc, opr1, opr2);
        }
        */
        else if (p32_asm::is_label(opr2)) {
            uint32_t label_addr;
            get_label_addr(opr2, label_addr);
            ts_rd_imm.encode(code, opc, opr1, label_addr);
        }
        else {
            std::cerr << "syntax error: " << file_name << ":"
                << line_num << ":" <<  line << std::endl;
        }
    }
    else if (p32_asm::is_immediate(opr1)) {
        ts_imm.encode(code, opc, opr1);
    }
    else if (p32_asm::is_label(opr1)) {
        uint32_t label_addr;

        if (get_label_addr(opr1, label_addr)) {
            /*
            if ((label_addr - current) < 0x10000) {
                ts_imm.encode(out, opc, opr1);
            }
            else {
                ts_rd.encode(out, opc, opr1);
            }
            */
        }
    }
    else if (p32_asm::is_reference(opr1)) {
        ts_ref_rs.encode(code, opc, opr1, opr2);
    }
    /*
    else if (is_reference_offset(opr1)) {
        refoff_rd.encode(opc, opr1, opr2);
    }
    */
    else {
        std::cerr << "syntax error: " << file_name << ":"
            << line_num << ":" <<  line << std::endl;
    }

    for (auto i : code) {
        std::cout << std::hex << i << std::endl;
        ofs.write(reinterpret_cast<const char*>(&i), sizeof(uint32_t));
    }
}

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    std::string in_file_name = argv[1];
    std::string out_file_name;

    if (argc < 3) {
        out_file_name = "a.out";
    }
    else {
        out_file_name = argv[2];
    }

    std::ifstream ifs(in_file_name);
    std::ofstream ofs(out_file_name, std::ios_base::binary);
    //std::string line;
    char line[256];
    const std::regex re("^[ \\t]*(?:([\\w\\.]+)[ \\t]*:)?[ \\t]*(?:(\\w+)[ \\t]+([^, \\t]+)[ \\t]*(?:,[ \\t]*([^ \\t]+))?)?.*");
    std::cmatch cm;
    uint32_t current = 0;
    uint32_t line_num = 1;

    while (ifs.getline(line, 256)) {
        if (std::regex_match(line, cm, re)) {
            std::cout << "--- match ---" << std::endl;
            if (cm[1].length() > 0) {
                std::cout << "label:\t\t'" << cm[1] << "'" << std::endl;
                strtbl[cm[1].str()] = current + 4;
            }

            if (cm[2].length() > 0) {
                /*
                std::cout << "opcode:\t\t'" << cm[2] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[3] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[4] << "'" << std::endl;
                translate(in_file_name, line_num, ofs,
                          current, cm[2], cm[3], cm[4], line);
                          */
                current += 4;
            }
        }
        ++line_num;
    }

    std::cout << "strtbl:" << std::endl;
    for (auto i : strtbl) {
        std::cout << i.first << " " << std::hex << i.second << std::endl;
    }

    ifs.clear();
    ifs.seekg(0, ifs.beg);

    while (ifs.getline(line, 256)) {
        if (std::regex_match(line, cm, re)) {
            std::cout << "--- match ---" << std::endl;
            /*
            if (cm[1].length() > 0) {
                std::cout << "label:\t\t'" << cm[1] << "'" << std::endl;
                strtbl[cm[1].str()] = current + 4;
            }
            */

            if (cm[2].length() > 0) {
                std::cout << "opcode:\t\t'" << cm[2] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[3] << "'" << std::endl;
                std::cout << "operand:\t'" << cm[4] << "'" << std::endl;
                translate(in_file_name, line_num, ofs,
                          current, cm[2], cm[3], cm[4], line);
                current += 4;
            }
        }
        ++line_num;

    }

    ifs.close();
    ofs.close();

    return EXIT_SUCCESS;
}

