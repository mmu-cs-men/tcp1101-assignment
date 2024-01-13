#pragma once
enum class TokenType
{
    Opcode,
    Register,
    Whitespace,
    Newline,
    Comma,
    OpenBracket,
    ClosedBracket,
    NumLiteral,
    Eof
};