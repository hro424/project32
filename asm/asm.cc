#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>


int
main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]);
    std::string line;
    std::regex re("^[ \\t]*(?:([\\w\\.]+)[ \\t]*:)?[ \\t]*(?:(\\w+)[ \\t]+(@?\\w+)[ \\t]*(?:,[ \\t]*(@?\\w+))?)?.*");
    std::cmatch cm;
    std::map<std::string, uint32_t> symbols;
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

    for (auto i : symbols) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}
