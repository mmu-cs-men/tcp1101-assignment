/*
    This file mainly serves as a test code for the lexer
    To compile this file, in the terminal paste "g++ --std=c++20 Lexer.cpp Test_Lexer.cpp Token.cpp -o Test_Lexer"
    To run paste .\Test_Lexer
*/




#include "Lexer.h"
#include <iostream>
#include <string>

std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::UnaryOpcode:
        return "UnaryOpcode";
        break;
    case TokenType::MovOpcode:
        return "MovOpcode";
        break;
    case TokenType::ArithmeticOpcode:
        return "ArithmeticOpcode";
        break;
    case TokenType::BitwiseOpcode:
        return "BitwiseOpcode";
        break;
    case TokenType::SerialOpcode:
        return "SerialOpcode";
        break;
    case TokenType::Register:
        return "Register";
        break;
    case TokenType::Whitespace:
        return "Whitespace";
        break;
    case TokenType::Newline:
        return "Newline";
        break;
    case TokenType::Comma:
        return "Comma";
        break;
    case TokenType::OpenBracket:
        return "OpenBracket";
        break;
    case TokenType::ClosedBracket:
        return "CloseBracket";
        break;
    case TokenType::NumLiteral:
        return "NumLiteral";
        break;
    case TokenType::Eof:
        return "Eof";
        break;
    // Add cases for other TokenType values
    default:
        return "UnknownType";
    }
}

int main()
{
    std::string asmCode = "ADD [R1] , [R2]"; // Sample ASM code
    Lexer lexer(asmCode);
    auto tokens = lexer.getTokens();

    // Print each token
    for (auto &token : tokens)
    {
        std::cout << tokenTypeToString(token.getType()) << ",";
    }
    std::cout << std::endl;
    return 0;
}