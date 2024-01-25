#pragma once
#include "TokenType.h"
#include <string>

class Token
{
    public:
        Token(TokenType type, std::string content);
        std::string getContent();
        TokenType getType();

    private:
        std::string content;
        TokenType type;
};