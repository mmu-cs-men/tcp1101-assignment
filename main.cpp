#include "Lexer.h"
#include "MachineState.h"
#include "Parser.h"
#include "Runner.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// clang-format off

// Compile like this:
// g++ -std=c++11 main.cpp Lexer.cpp MachineState.cpp Runner.cpp Parser.cpp Token.cpp -o main

// clang-format on

void stringToFile(std::string &dump)
{
    int fileCount = 1;
    std::string outputFileName;
    std::ifstream existingFile;

    // Check for existing files and increment fileCount to get the next file
    // number
    do
    {
        outputFileName = "main_" + std::to_string(fileCount) + ".txt";
        existingFile.open(outputFileName);
        if (existingFile.is_open())
        {
            fileCount++;
            existingFile.close();
        }
    } while (existingFile);

    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << dump;
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to create file " << outputFileName << std::endl;
    }
}

int main()
{
    std::string filePath;
    std::cout << "Please enter path to an .asm file. Relative path recommended."
              << std::endl;
    std::cout << "Input file path: ";
    std::getline(std::cin, filePath);

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
    std::string dump = machineState.dumpState();
    std::cout << dump;

    stringToFile(dump);
}
