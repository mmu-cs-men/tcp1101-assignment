#pragma once
enum class TokenType
{
    UnaryOpcodem,
    MovOpcode,
    ArithmeticOpcode,
    BitwiseOpcode,
    SerialOpcode,
    Register,
    Whitespace,
    Newline,
    Comma,
    OpenBracket,
    ClosedBracket,
    NumLiteral,
    Eof
};