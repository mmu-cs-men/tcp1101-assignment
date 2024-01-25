#pragma once
#include "Token.h"
#include <string>
#include <vector>

class Lexer
{
    public:
        /**
         * @brief Initializes a Lexer object with the given program as input.
         *
         * @param program The input program as a string.
         */
        Lexer(std::string program);
        /**
         * @brief Processes the input program and extracts tokens.
         *
         * This function iterates over the input program and uses the readWord
         * function to extract words and delimiters. It then categorizes each
         * word or delimiter into a token with a specific TokenType. Each token
         * is then added to a vector of tokens which is returned at the end of
         * the function.
         *
         * @return A vector of Token objects representing the categorized words
         * and delimiters from the input program.
         */
        std::vector<Token> getTokens();

    private:
        std::string inputProgram;
        int currentPosition = 0;

        /**
         * @brief Reads the next word from the input program.
         *
         * This function reads the next word from the current position in the
         * input program. A word is defined as a sequence of characters that
         * does not include spaces, commas, newlines, or square brackets. These
         * characters are considered delimiters and are returned as separate
         * words. Consecutive spaces are condensed into a single space.
         *
         * @return A string representing the next word or delimiter in the input
         * program.
         */
        std::string readWord();
};