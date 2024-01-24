#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include <string>
#include <vector>

int main()
{
    std::string code = "MOV R1, 5\nADD R1, 6\nMOV R1, R3\nMUL            R3, "
                       "4\nSTORE R3, 20\nSTORE R1, 14";

    Lexer lexer(code);

    std::vector<Token> tokenList = lexer.getTokens();

    Parser parser(tokenList);
    parser.parse();
}