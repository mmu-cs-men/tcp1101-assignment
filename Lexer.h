#pragma once
#include "Token.h"
#include <string>
#include <vector>

class Lexer
{
    public:
        Lexer(std::string program);
        std::vector<Token> getTokens();

    private:
        std::string inputProgram;
        int currentPosition = 0;

        std::string readWord();
};