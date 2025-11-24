#pragma once // Expression.hpp

#include "Token.hpp"
#include <queue>

// One assignment: VAR = <expression>
struct Expression
{
    char varName;          // 'A'..'Z'
    std::queue<Token> rpn; // 'Reverse Polish Notation' for the right-hand side

    Expression()
        : varName('\0'),
          rpn()
    {
    }
};