#include "Lexer.h"
#include "MachineState.h"
#include "Parser.h"
#include "Runner.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string filePath;
    std::cout << "Please enter path to an .asm file. You may enter an absolute "
                 "or relative path."
              << std::endl;
    std::cout << "Input file path: ";
    std::cin >> filePath;

    std::ifstream file(filePath);
    if (!file)
    {
        std::cout << "Unable to open file " << filePath << std::endl
                  << std::endl;
        return 1;
    }

    std::string fileContent;
    std::getline(file, fileContent, '\0');
    file.close();

    Lexer lexer(fileContent);
    MachineState machineState;
    Runner runner(machineState);
    std::vector<Token> tokenList = lexer.getTokens();
    Parser parser(tokenList, runner);
    parser.parse();
    machineState.dumpState();
}