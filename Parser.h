#pragma once
#include "Runner.h"
#include "Token.h"
#include "TokenType.h"
#include <vector>

class Parser
{
    public:
        Parser(const std::vector<Token> &tokens, Runner &runner);
        void parse();

    private:
        std::vector<Token> tokenList;
        int tokenIndex = 0;
        Token currentToken;
        Runner &runner;

        void nextToken();
        void skipWhitespace();
        void skipComma();
        void unaryInstruction();
        void movInstruction();
        void arithmeticInstruction();
        void bitwiseInstruction();
        void serialInstruction();
        void instruction();
};