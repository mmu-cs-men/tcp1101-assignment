#pragma once
#include <string>
#include <vector>
#include "Token.h"

class Lexer 
{
    public:

        /**
         * Constructs a Lexer object.
         * @param program ASM code as a string to be tokenized.
         */
        Lexer(std::string program);

        /**
         * Method declaration
         * Process ASM code and identify tokens
         * returns tokens as a vector of <Token>
         * For example ASM CODE of "IN  R0" will return a vector containing tokens UnaryOpcode, Whitespace, and Register
         */
        std::vector<Token>getTokens();
        
    private:
        // Holds ASM program as string 
        // Input that lexer will process
        std::string intputProgram;

        // Tracks current possition in the input program during tokenization 
        // Determins where in the ASM code lexer is during tokenization process
        int currentPosition;

};