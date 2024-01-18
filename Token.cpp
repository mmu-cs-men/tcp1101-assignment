#include "Token.h"
#include <string>

// I'm not gonna overcomplicate this by putting input validation, sorry not sorry!
Token::Token(TokenType _type, std::string _content)
{
    type = _type;
    content = _content;
}

std::string Token::getContent()
{
    return content;
}

TokenType Token::getType()
{
    return type;
}