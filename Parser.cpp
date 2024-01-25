#include "Parser.h"
#include "Runner.h"
#include <cstdlib>
#include <iostream>

Parser::Parser(const std::vector<Token> &tokens, Runner &runner)
    : tokenList(tokens), currentToken(tokens[0]), runner(runner)
{
}

Token Parser::getPrevToken()
{
    return tokenList[tokenIndex - 1];
}

void Parser::throwSyntaxError(std::string errorMsg)
{
    std::cout << "Syntax error at line " << lineCounter << ". " << errorMsg
              << "." << std::endl;
    std::exit(EXIT_FAILURE);
}

void Parser::assertRegister(const std::string opcode)
{
    if (currentToken.getType() != TokenType::Register)
    {
        throwSyntaxError("Expected register after " + opcode);
    }
}

void Parser::assertWhitespace()
{
    if (currentToken.getType() != TokenType::Whitespace)
    {
        throwSyntaxError("Expected whitespace after " +
                         getPrevToken().getContent());
    }
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
        if (currentToken.getType() == TokenType::Newline)
        {
            lineCounter++;
        }
        nextToken();
    }
}

void Parser::skipComma()
{
    skipWhitespace();

    if (currentToken.getType() != TokenType::Comma)
    {
        throwSyntaxError("Expected a comma");
    }

    nextToken();
    skipWhitespace();
}

void Parser::unaryInstruction()
{
    std::string opcode = currentToken.getContent();
    assertWhitespace();
    skipWhitespace();
    assertRegister(opcode);
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
    else
    {
        std::cout << "Something has gone terribly wrong..." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Parser::movInstruction()
{
    nextToken();
    assertWhitespace();
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
        skipWhitespace();

        assertRegister("[");
        value = runner.getValueAtAddress(
            runner.getValueAtRegister(std::stoi(currentToken.getContent())));
        nextToken();
        skipWhitespace();
        if (currentToken.getType() != TokenType::ClosedBracket)
        {
            throwSyntaxError("Expected ']' after register");
        }
    }

    nextToken();
    skipComma();

    assertRegister(",");
    int registerNum = std::stoi(currentToken.getContent());
    runner.mov(value, registerNum);
}

void Parser::arithmeticInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    assertWhitespace();
    skipWhitespace();

    assertRegister(opcode);
    int firstRegister = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    assertRegister(",");
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
    else
    {
        std::cout << "Something has gone terribly wrong..." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Parser::bitwiseInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    assertWhitespace();
    skipWhitespace();

    assertRegister(opcode);

    int registerNum = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    if (currentToken.getType() != TokenType::NumLiteral)
    {
        throwSyntaxError("Expected a number but got: " +
                         currentToken.getContent());
    }

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
    else
    {
        std::cout << "Something has gone terribly wrong..." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Parser::serialInstruction()
{
    std::string opcode = currentToken.getContent();
    nextToken();
    assertWhitespace();
    skipWhitespace();
    assertRegister(opcode);

    int registerNum = std::stoi(currentToken.getContent());
    nextToken();
    skipComma();

    int address;
    if (currentToken.getType() == TokenType::NumLiteral)
    {
        address = std::stoi(currentToken.getContent());
        if (address < 0 || address > 63)
        {
            throwSyntaxError("Address out of range (0-63): " +
                             currentToken.getContent());
        }
    }
    else if (currentToken.getType() == TokenType::OpenBracket)
    {
        nextToken();
        skipWhitespace();
        assertRegister("[");

        address =
            runner.getValueAtRegister(std::stoi(currentToken.getContent()));

        nextToken();
        skipWhitespace();

        if (currentToken.getType() != TokenType::ClosedBracket)
        {
            throwSyntaxError("Expected ']' after register");
        }
    }

    if (opcode == "LOAD")
    {
        runner.load(registerNum, address);
    }
    else if (opcode == "STORE")
    {
        runner.store(registerNum, address);
    }
    else
    {
        std::cout << "Something has gone terribly wrong..." << std::endl;
        std::exit(EXIT_FAILURE);
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
    else
    {
        std::string error = "Expected an opcode. Found " +
                            currentToken.getContent() + " instead";
        throwSyntaxError(error);
    }
}

void Parser::parse()
{
    while (currentToken.getType() != TokenType::Eof)
    {
        skipWhitespace();
        instruction();
        nextToken();
    }
}
