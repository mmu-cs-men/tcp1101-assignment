#include "Parser.h"
#include "Runner.h"

Parser::Parser(const std::vector<Token> &tokens, Runner &runner)
    : tokenList(tokens), currentToken(tokens[0]), runner(runner)
{
}

void Parser::nextToken()
{
    currentToken = tokenList[++tokenIndex];
}

void Parser::skipWhitespace()
{
    while (currentToken.getType() == TokenType::Whitespace ||
           currentToken.getType() == TokenType::Newline)
    {
        nextToken();
    }
}

void Parser::skipComma()
{
    skipWhitespace();
    nextToken();
    skipWhitespace();
}

void Parser::unaryInstruction()
{
    std::string opcode = currentToken.getContent();
    skipWhitespace();
    int registerNum = std::stoi(currentToken.getContent());

    if (opcode == "IN")
    {
        runner.in(registerNum);
    }
    else if (opcode == "OUT")
    {
        runner.out(registerNum);
    }
    else if (opcode == "INC")
    {
        runner.inc(registerNum);
    }
    else if (opcode == "DEC")
    {
        runner.dec(registerNum);
    }
}

void Parser::movInstruction()
{
    nextToken();
    skipWhitespace();

    int value;
    if (currentToken.getType() == TokenType::NumLiteral)
    {
        value = std::stoi(currentToken.getContent());
    }
    else if (currentToken.getType() == TokenType::Register)
    {
        value = runner.getValueAtRegister(std::stoi(currentToken.getContent()));
    }
    else if (currentToken.getType() == TokenType::OpenBracket)
    {
        nextToken();
        value = runner.getValueAtAddress(
            runner.getValueAtRegister(std::stoi(currentToken.getContent())));
        nextToken();
    }

    nextToken();
    skipComma();

    int registerNum = std::stoi(currentToken.getContent());
    runner.mov(value, registerNum);
}

void Parser::arithmeticInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    skipWhitespace();

    int firstRegister = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    int secondRegister = std::stoi(currentToken.getContent());

    if (opcode == "ADD")
    {
        runner.add(firstRegister, secondRegister);
    }
    else if (opcode == "SUB")
    {
        runner.sub(firstRegister, secondRegister);
    }
    else if (opcode == "MUL")
    {
        runner.mul(firstRegister, secondRegister);
    }
    else if (opcode == "DIV")
    {
        runner.div(firstRegister, secondRegister);
    }
}

void Parser::bitwiseInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    skipWhitespace();

    int registerNum = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    int value = std::stoi(currentToken.getContent());

    if (opcode == "ROL")
    {
        runner.rol(registerNum, value);
    }
    else if (opcode == "ROR")
    {
        runner.ror(registerNum, value);
    }
    else if (opcode == "SHL")
    {
        runner.shl(registerNum, value);
    }
    else if (opcode == "SHR")
    {
        runner.shr(registerNum, value);
    }
}

void Parser::serialInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    skipWhitespace();

    int registerNum = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    int address;
    if (currentToken.getType() == TokenType::NumLiteral)
    {
        address = std::stoi(currentToken.getContent());
    }
    else if (currentToken.getType() == TokenType::OpenBracket)
    {
        nextToken();
        address =
            runner.getValueAtRegister(std::stoi(currentToken.getContent()));
        nextToken();
    }

    if (opcode == "LOAD")
    {
        runner.load(registerNum, address);
    }
    else if (opcode == "STORE")
    {
        runner.store(registerNum, address);
    }
}

void Parser::instruction()
{
    if (currentToken.getType() == TokenType::UnaryOpcode)
    {
        unaryInstruction();
    }
    else if (currentToken.getType() == TokenType::MovOpcode)
    {
        movInstruction();
    }
    else if (currentToken.getType() == TokenType::ArithmeticOpcode)
    {
        arithmeticInstruction();
    }
    else if (currentToken.getType() == TokenType::BitwiseOpcode)
    {
        bitwiseInstruction();
    }
    else if (currentToken.getType() == TokenType::SerialOpcode)
    {
        serialInstruction();
    }
}

void Parser::parse()
{
    while (currentToken.getType() != TokenType::Eof)
    {
        instruction();
        nextToken();
        skipWhitespace();
    }
}
