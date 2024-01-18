#pragma once
#include "TokenType.h"
#include <string>

class Token
{
    public:
        /**
         * @brief Constructs a Token object with the specified type and content.
         *
         * @param _type The type of the token.
         * @param _content The content of the token. For example, if type is `TokenType::UnaryOpcode`, content must be
         * either IN, OUT, INC, DEC
         */
        Token(TokenType _type, std::string _content);

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