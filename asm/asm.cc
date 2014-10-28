#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

namespace {
struct Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2) = 0;
};

struct MovTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

struct JmpTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

struct CmpTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

struct AddTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

uint32_t
ArithTranslator::encode(std::string& op, std::string& opr1 std::string& opr2)
{
	if (opr1.length() == 0 || opr2.length() == 0) {
		// syntax error
	}

	if (opr2.isnumber()) {
		code = ((0x8500 | op) << 16) | (opr1.reg() << 20) | (opr2.number() & 0xFFFF);
	}
	else {
		code = (0x8100 << 16) | (opr1.reg() << 20) | (opr2.reg() << 16) | op << 12;
	}
}

struct SubTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

struct BranchTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

struct SwapTranslator : public Translator
{
    virtual uint32_t encode(std::string& opr1, std::string& opr2);
};

std::map<std::string, uint32_t> symbols;
std::map<std::string, Translator> translator;

int
translate(std::string& opc, std::string& opr1, std::string& opr2)
{
    translator[opc].encode(opr1, opr2);
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
