#include "Lexer.h"
#include "Token.h"
#include "TokenType.h"
#include <iostream>

/**
 * Class Lexer Definition
 * @param program String containing ASM code to be tokenized
 * @note - inputProgram --> set to program string (which contains ASM code)
 * @note - currentPosstion --> initialized to 0, indicating the start of tokenization process
 */
Lexer::Lexer(std::string program) : inputProgram(program), currentPosition(0)
{
}

std::string Lexer::readWord()
{
    if (inputProgram[currentPosition] == ' ')
    {
        // Handle whitespaces and only returns 1 whitespace eventhough program has multiple
        while (currentPosition < inputProgram.length() && (inputProgram[currentPosition] == ' '))
        {
            currentPosition++;
        }
        return " ";
    }

    if (inputProgram[currentPosition] == ',' || inputProgram[currentPosition] == '\n')
    {
        /**
         * new string containing object with lenght of 1
         * inputProgram[currentPosition++] --> char to be placed in the new string
         * Char of current posistion of inputProgram
         * currentPosition++ --> increment to move to next char in inputProgram
         */
        return std::string(1, inputProgram[currentPosition++]);
    }

    // Reads word until hitting space , comma , newline
    std::string word;
    while (currentPosition < inputProgram.length() && inputProgram[currentPosition != ' '] &&
           inputProgram[currentPosition] != ',' && inputProgram[currentPosition] != '\n')
    {
        word += inputProgram[currentPosition];
        currentPosition++;
    }

    return word;
}

/**
 * @note - Method from member of Lexer Class
 * @note - Analyzes input program and breaks it down into tokens
 * @note - Returns a vector containing object type Token
 */
std::vector<Token> Lexer::getTokens()
{
    // - vector that stores 'Token' as program processes input program(ASM Code)
    std::vector<Token> tokens;

    while (currentPosition < inputProgram.length())
    {

        // Read word from current position
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
        else if (word == "IN" || word == "OUT" || word == "INC" || word == "DEC")
        {
            tokens.push_back(Token(TokenType::UnaryOpcode, word));
        }

        // Register handler
        else if (word == "R0" || word == "R1" || word == "R2" || word == "R3" || word == "R4" || word == "R5" ||
                 word == "R6")
        {
            tokens.push_back(Token(TokenType::Register, word));
        }

        // MovOpcode handler
        else if (word == "MOV")
        {
            tokens.push_back(Token(TokenType::MovOpcode, word));
        }

        // ArithmeticOpcode handler
        else if (word == "ADD" || word == "SUB" || word == "MUL" || word == "DIV")
        {
            tokens.push_back(Token(TokenType::ArithmeticOpcode, word));
        }

        // BitwiseOpcode handler
        else if(word == "ROL" || word == "ROR" || word == "SHL" || word == "SHR")
        {
            tokens.push_back(Token(TokenType::BitwiseOpcode,word));
        }

        // SerialOpcode handler
        else if(word == "LOAD" || word == "STORE")
        {
            tokens.push_back(Token(TokenType::SerialOpcode,word));
        }

        // OpenBracket handler
        else if(word == "[")
        {
            tokens.push_back(Token(TokenType::OpenBracket,word));
        }

        // CloseBracket handler
        else if(word == "]")
        {
            tokens.push_back(Token(TokenType::OpenBracket,word));
        }
        
        // NumLiteral handler
        else if(!word.empty() && std::isdigit(word[0])) 
        {
            tokens.push_back(Token(TokenType::NumLiteral,word));
        }
    }
    
    // Eof handler
    tokens.push_back(Token(TokenType::Eof,""));

    return tokens;
}