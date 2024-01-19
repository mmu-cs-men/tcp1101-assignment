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
    std::string word;
    
    // Skips spases and commas in the start of the program  
    while (currentPosition < inputProgram.length() && (inputProgram[currentPosition] == ' ') ||
           (inputProgram[currentPosition] == ','))
    {
        currentPosition++;
    }

    // Reads word until space or comma or newline
    while (currentPosition < inputProgram.length() &&
           (inputProgram[currentPosition] != ' ' && inputProgram[currentPosition] != ',' &&
            inputProgram[currentPosition] != '\n'))
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
        //Read word from current position
        std::string word = readWord();

        if (word == "IN" ||word == "OUT" || word == "INC" || word == "DEC" ){
            tokens.push_back(Token(TokenType:: UnaryOpcode,word));

            currentPosition++;
            
        }
    }

    return tokens;
}