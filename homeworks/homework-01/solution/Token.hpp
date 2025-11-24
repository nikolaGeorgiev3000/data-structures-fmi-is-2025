#pragma once // Token.hpp

#include <cstddef> // size_t

// All possible token kinds in the expression language
enum class TokenType
{
    Number,
    Variable,

    Plus,
    Minus,
    Mul,
    Div,
    Pow,

    UnaryPlus,
    UnaryMinus,

    LParen,
    RParen,
    Semicolon, // Argument separator inside function calls

    Function, // MIN, MAX, AVG, SUM, PRD in the operator stack / RPN
    End       // Sentinel, if needed by the parser
};

// Supported function identifiers
enum class FunctionId
{
    Min,
    Max,
    Avg,
    Sum,
    Prd
};

struct Token
{
    TokenType type;

    // For numbers
    double numberValue;

    // For variables
    char varName; // Stored as uppercase letter 'A' .. 'Z'

    // For functions
    FunctionId funcId; // Valid only when type == Function
    int argCount;      // Used in RPN to know how many arguments to pop

    Token()
        : type(TokenType::End),
          numberValue(0.0),
          varName('\0'),
          funcId(FunctionId::Sum),
          argCount(0)
    {
    }
};

// Operator helpers

inline bool isBinaryOperator(TokenType t)
{
    return t == TokenType::Plus ||
           t == TokenType::Minus ||
           t == TokenType::Mul ||
           t == TokenType::Div ||
           t == TokenType::Pow;
}

inline bool isUnaryOperator(TokenType t)
{
    return t == TokenType::UnaryPlus ||
           t == TokenType::UnaryMinus;
}

inline int precedence(TokenType t)
{
    // Higher value -> higher precedence
    switch (t)
    {
    case TokenType::UnaryPlus:
    case TokenType::UnaryMinus:
        return 4; // Highest (applied to a single operand)

    case TokenType::Pow:
        return 3; // Exponentiation

    case TokenType::Mul:
    case TokenType::Div:
        return 2;

    case TokenType::Plus:
    case TokenType::Minus:
        return 1;

    default:
        return 0;
    }
}

// Returns true for right-associative operators (i.e. exp and unary ops)
inline bool isRightAssociative(TokenType t)
{
    return t == TokenType::Pow ||
           t == TokenType::UnaryPlus ||
           t == TokenType::UnaryMinus;
}

inline bool isLeftAssociative(TokenType t)
{
    return isBinaryOperator(t) && !isRightAssociative(t);
}