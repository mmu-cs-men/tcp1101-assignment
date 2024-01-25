#include "Token.h"
#include <string>

// I'm not gonna overcomplicate this by putting input validation, sorry not
// sorry!
Token::Token(TokenType type, std::string content) : type(type), content(content)
{
}

std::string Token::getContent()
{
    return content;
}

TokenType Token::getType()
{
    return type;
}