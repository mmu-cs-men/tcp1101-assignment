#include "Parser.h"
#include <iostream> // Include for debug output

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
        // Runner.in(registerNum);
        std::cout << "IN " << registerNum << std::endl;
    }
    else if (opcode == "OUT")
    {
        // Runner.out(registerNum);
        std::cout << "OUT " << registerNum << std::endl;
    }
    else if (opcode == "INC")
    {
        // Runner.inc(registerNum);
        std::cout << "INC " << registerNum << std::endl;
    }
    else if (opcode == "DEC")
    {
        // Runner.dec(registerNum);
        std::cout << "DEC " << registerNum << std::endl;
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
        // value =
        // Runner.getValueAtRegister(std::stoi(currentToken.getContent()));
        value = std::stoi(currentToken.getContent()); // Placeholder for debug
        std::cout << "MOV from Register " << value << std::endl;
    }
    else if (currentToken.getType() == TokenType::OpenBracket)
    {
        nextToken();
        // value =
        // Runner.getValueAtAddress(Runner.getValueAtRegister(std::stoi(currentToken.getContent())));
        value = std::stoi(currentToken.getContent()); // Placeholder for debug
        std::cout << "MOV from Address " << value << std::endl;
        nextToken();
    }

    nextToken();
    skipComma();

    int registerNum = std::stoi(currentToken.getContent());
    // Runner.mov(value, registerNum);
    std::cout << "MOV " << value << " to " << registerNum << std::endl;
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
        // Runner.add(firstRegister, secondRegister);
        std::cout << "ADD " << firstRegister << " " << secondRegister
                  << std::endl;
    }
    else if (opcode == "SUB")
    {
        // Runner.sub(firstRegister, secondRegister);
        std::cout << "SUB " << firstRegister << " " << secondRegister
                  << std::endl;
    }
    else if (opcode == "MUL")
    {
        // Runner.mul(firstRegister, secondRegister);
        std::cout << "MUL " << firstRegister << " " << secondRegister
                  << std::endl;
    }
    else if (opcode == "DIV")
    {
        // Runner.div(firstRegister, secondRegister);
        std::cout << "DIV " << firstRegister << " " << secondRegister
                  << std::endl;
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
        // Runner.rol(registerNum, value);
        std::cout << "ROL " << registerNum << " " << value << std::endl;
    }
    else if (opcode == "ROR")
    {
        // Runner.ror(registerNum, value);
        std::cout << "ROR " << registerNum << " " << value << std::endl;
    }
    else if (opcode == "SHL")
    {
        // Runner.shl(registerNum, value);
        std::cout << "SHL " << registerNum << " " << value << std::endl;
    }
    else if (opcode == "SHR")
    {
        // Runner.shr(registerNum, value);
        std::cout << "SHR " << registerNum << " " << value << std::endl;
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
        // address =
        // Runner.getValueAtRegister(std::stoi(currentToken.getContent()));
        address = std::stoi(currentToken.getContent()); // Placeholder for debug
        std::cout << "Serial Instruction Address " << address << std::endl;
        nextToken();
    }

    // Runner calls commented out and replaced with debug output
    if (opcode == "LOAD")
    {
        // Runner.load(registerNum, address);
        std::cout << "LOAD " << registerNum << " " << address << std::endl;
    }
    else if (opcode == "STORE")
    {
        // Runner.store(registerNum, address);
        std::cout << "STORE " << registerNum << " " << address << std::endl;
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
