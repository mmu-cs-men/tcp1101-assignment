#pragma once

/**
 * @brief Enum representing the different types of tokens that can be
 * encountered in the assignment.
 */
enum class TokenType
{
    UnaryOpcode,      // IN, OUT, INC, DEC
    MovOpcode,        // MOV
    ArithmeticOpcode, // ADD, SUB, MUL, DIV
    BitwiseOpcode,    // ROL, ROR, SHL, SHR
    SerialOpcode,     // LOAD, STORE
    Register,         // R0, R1, R2, R3, R4, R5, R6
    Whitespace,       // " "
    Newline,          // \n
    Comma,            // ,
    OpenBracket,      // [
    ClosedBracket,    // ]
    NumLiteral,       // 0,1,2,3,...,255
    Eof               // ""
};