#include "Token.h"
#include <string>

Token::Token(TokenType type, std::string content)
{
    this->type = type;
    this->content = content;
}

std::string Token::getContent()
{
    return content;
}

TokenType Token::getType()
{
    return type;
}