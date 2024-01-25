#pragma once
#include "TokenType.h"
#include <string>

class Token
{
    public:
        /**
         * @brief Construct a new Token object.
         *
         * @param type The type of the token as defined in TokenType.
         * @param content The string content of the token.
         */
        Token(TokenType type, std::string content);

        std::string getContent();

        TokenType getType();

    private:
        std::string content;
        TokenType type;
};