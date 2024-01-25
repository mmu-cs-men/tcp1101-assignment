#include "Lexer.h"
#include "Token.h"
#include "TokenType.h"
#include <iostream>

Lexer::Lexer(std::string program) : inputProgram(program)
{
}

std::string Lexer::readWord()
{
    if (inputProgram[currentPosition] == ' ')
    {
        // Handle whitespaces and only returns 1 whitespace even though program
        // has multiple
        while (currentPosition < inputProgram.length() &&
               (inputProgram[currentPosition] == ' '))
        {
            currentPosition++;
        }
        return " ";
    }

    if (inputProgram[currentPosition] == ',' ||
        inputProgram[currentPosition] == '\n')
    {
        return std::string(1, inputProgram[currentPosition++]);
    }

    if (inputProgram[currentPosition] == '[' ||
        inputProgram[currentPosition] == ']')
    {
        return std::string(1, inputProgram[currentPosition++]);
    }

    std::string word;
    while (currentPosition < inputProgram.length() &&
           inputProgram[currentPosition] != ' ' &&
           inputProgram[currentPosition] != ',' &&
           inputProgram[currentPosition] != '\n' &&
           inputProgram[currentPosition] != '[' &&
           inputProgram[currentPosition] != ']')
    {
        word += inputProgram[currentPosition++];
    }
    return word;
}

std::vector<Token> Lexer::getTokens()
{
    std::vector<Token> tokens;

    while (currentPosition < inputProgram.length())
    {

        std::string word = readWord();

        // Whitespace handler
        if (word == " ")
        {
            tokens.push_back(Token(TokenType::Whitespace, word));
        }

        // Comma handler
        else if (word == ",")
        {
            tokens.push_back(Token(TokenType::Comma, word));
        }

        // Newline handler
        else if (word == "\n")
        {
            tokens.push_back(Token(TokenType::Newline, word));
        }

        // UnaryOpcode handler
        else if (word == "IN" || word == "OUT" || word == "INC" ||
                 word == "DEC")
        {
            tokens.push_back(Token(TokenType::UnaryOpcode, word));
        }

        // Register handler
        else if (word == "R0" || word == "R1" || word == "R2" || word == "R3" ||
                 word == "R4" || word == "R5" || word == "R6")
        {
            tokens.push_back(Token(TokenType::Register, word.substr(1, 1)));
        }

        // MovOpcode handler
        else if (word == "MOV")
        {
            tokens.push_back(Token(TokenType::MovOpcode, word));
        }

        // ArithmeticOpcode handler
        else if (word == "ADD" || word == "SUB" || word == "MUL" ||
                 word == "DIV")
        {
            tokens.push_back(Token(TokenType::ArithmeticOpcode, word));
        }

        // BitwiseOpcode handler
        else if (word == "ROL" || word == "ROR" || word == "SHL" ||
                 word == "SHR")
        {
            tokens.push_back(Token(TokenType::BitwiseOpcode, word));
        }

        // SerialOpcode handler
        else if (word == "LOAD" || word == "STORE")
        {
            tokens.push_back(Token(TokenType::SerialOpcode, word));
        }

        // OpenBracket handler
        else if (word == "[")
        {
            tokens.push_back(Token(TokenType::OpenBracket, word));
        }

        // CloseBracket handler
        else if (word == "]")
        {
            tokens.push_back(Token(TokenType::ClosedBracket, word));
        }

        // NumLiteral handler
        else if (!word.empty() && std::isdigit(word[0]))
        {
            tokens.push_back(Token(TokenType::NumLiteral, word));
        }
    }

    // Handling Eof
    if (currentPosition >= inputProgram.length())
    {
        tokens.push_back(Token(TokenType::Eof, ""));
    }

    return tokens;
}