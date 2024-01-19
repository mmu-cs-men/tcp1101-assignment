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
         * @brief - Declaration of getTokens method
         * @note  - Process ASM code and identify tokens.
         * @note  - Returns tokens as a vector of <Token>.
         * @note  - Example: "IN  R0" will return a vector containing tokens UnaryOpcode, Whitespace, and Register.
         */
        std::vector<Token>getTokens();
        
    private:
        // Holds ASM program as string 
        // Input that lexer will process
        std::string inputProgram;

        // Tracks current possition in the input program during tokenization. 
        // Determins where in the ASM code lexer is during tokenization process.
        int currentPosition;

        /**
         * @brief Declaration of readWord mehtod. 
         * @note - Member variable of class Lexer.
         * @note - Operates on'inputProgram' & 'currentPosition'
         * @param -None
         * @return - string.
        */
        std::string readWord();

};