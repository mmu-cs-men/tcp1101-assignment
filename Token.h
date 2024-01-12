#pragma once
#include "TokenType.h"
#include <string>

/**
 * @brief Represents a token in the program.
 */
class Token
{
    public:
        /**
         * @brief Constructs a new Token object.
         *
         * @param type The type of the token.
         * @param content The content of the token. Content for TokenType::Register should be in the form of 0-6. For
         * example, R0 is 0 and R4 is 4. TokenType::NumLiteral should be an integer. TokenType::Opcode should be the
         * 'MOV', 'ADD', etc. The content for all other token types doesn't really matter but should be an empty string.
         */
        Token(TokenType type, std::string content);

        /**
         * @brief Gets the content of the token.
         *
         * @return The content of the token.
         */
        std::string getContent();

        /**
         * @brief Gets the type of the token.
         *
         * @return The type of the token.
         */
        TokenType getType();

    private:
        std::string content;
        TokenType type;
};