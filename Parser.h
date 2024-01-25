#pragma once
#include "Runner.h"
#include "Token.h"
#include "TokenType.h"
#include <string>
#include <vector>

class Parser
{
    public:
        /**
         * @brief Initializes a Parser object with the given tokens and runner.
         *
         * @param tokens The input tokens as a vector of Token objects.
         * @param runner The Runner object that will execute the parsed
         * instructions.
         */
        Parser(const std::vector<Token> &tokens, Runner &runner);

        /**
         * @brief Parses the tokens and executes the corresponding instructions.
         *
         * This function iterates over the tokens and based on the type of each
         * token, it calls the corresponding instruction function in the Runner
         * object. It continues parsing and executing until it encounters an Eof
         * token.
         */
        void parse();

    private:
        std::vector<Token> tokenList;
        int tokenIndex = 0;
        int lineCounter = 1;
        Token currentToken;
        Runner &runner;

        Token getPrevToken();
        void assertRegister(const std::string opcode);
        void assertWhitespace();
        void throwSyntaxError(std::string errorMsg);
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