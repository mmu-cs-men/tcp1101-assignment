#pragma once
#include "Token.h"
#include "TokenType.h"
#include <vector>

class Parser
{
    public:
        Parser(const std::vector<Token> &tokens);
        void parse();

    private:
        std::vector<Token> tokenList;
        int tokenIndex;
        Token currentToken = Token(TokenType::Eof, "");

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