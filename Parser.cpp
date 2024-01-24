#include "Parser.h"

Parser::Parser(const std::vector<Token> &tokens)
{
    tokenList = tokens;
    tokenIndex = 0;
    currentToken = tokens[0];
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
        Runner::in(registerNum);
    }
    else if (opcode == "OUT")
    {
        Runner::out(registerNum);
    }
    else if (opcode == "INC")
    {
        Runner::inc(registerNum);
    }
    else if (opcode == "DEC")
    {
        Runner::dec(registerNum);
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
        value =
            Runner::getValueAtRegister(std::stoi(currentToken.getContent()));
    }
    else if (currentToken.getType() == TokenType::OpenBracket)
    {
        nextToken();
        value = Runner::getValueAtAddress(
            Runner::getValueAtRegister(std::stoi(currentToken.getContent())));
        nextToken();
    }

    nextToken();
    skipComma();

    int registerNum = std::stoi(currentToken.getContent());
    Runner::mov(value, registerNum);
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
        Runner::add(firstRegister, secondRegister);
    }
    else if (opcode == "SUB")
    {
        Runner::sub(firstRegister, secondRegister);
    }
    else if (opcode == "MUL")
    {
        Runner::mul(firstRegister, secondRegister);
    }
    else if (opcode == "DIV")
    {
        Runner::div(firstRegister, secondRegister);
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
        Runner::rol(registerNum, value);
    }
    else if (opcode == "ROR")
    {
        Runner::ror(registerNum, value);
    }
    else if (opcode == "SHL")
    {
        Runner::shl(registerNum, value);
    }
    else if (opcode == "SHR")
    {
        Runner::shr(registerNum, value);
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
            Runner::getValueAtRegister(std::stoi(currentToken.getContent()));
        nextToken();
    }

    if (opcode == "LOAD")
    {
        Runner::load(registerNum, address);
    }
    else if (opcode == "STORE")
    {
        Runner::store(registerNum, address);
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
