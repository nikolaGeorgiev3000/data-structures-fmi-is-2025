#pragma once // Lexer.hpp

#include "Token.hpp"
#include "Utils.hpp"

#include <cstddef> // size_t

// Tries to parse a number starting at 'p'
// If successful: updates 'p' to point after the number, fills 'outToken', and returns 'true'
// If failed: 'p' remains unchanged, returns 'false'
inline bool tryParseNumber(const char*& p, Token& outToken)
{
    if (!isDigitChar(*p))
        return false;

    double value = 0.0;
    double frac = 0.0;
    double base = 0.1;
    bool hasDot = false;

    const char* curr = p;

    // Integer part
    while (isDigitChar(*curr))
    {
        value = value * 10.0 + (*curr - '0');
        ++curr;
    }

    // Fractional part
    if (*curr == '.')
    {
        hasDot = true;
        ++curr;
        while (isDigitChar(*curr))
        {
            frac += (*curr - '0') * base;
            base *= 0.1;
            ++curr;
        }
    }

    // Finalize token
    outToken.type = TokenType::Number;
    outToken.numberValue = value + frac;

    p = curr; // Update the main pointer
    return true;
}

// Helper function to check for supported function names
// Returns 'true' if a valid function name is found
inline bool parseFunctionId(const char* p, FunctionId& outId, size_t& len)
{
    size_t i = 0;
    while (isLetterChar(p[i]))
        ++i;

    // All current functions are exactly 3 characters long
    if (i != 3)
        return false;

    len = 3;
    if (equalsIgnoreCase(p, "MIN", 3))
    {
        outId = FunctionId::Min;
        return true;
    }
    if (equalsIgnoreCase(p, "MAX", 3))
    {
        outId = FunctionId::Max;
        return true;
    }
    if (equalsIgnoreCase(p, "AVG", 3))
    {
        outId = FunctionId::Avg;
        return true;
    }
    if (equalsIgnoreCase(p, "SUM", 3))
    {
        outId = FunctionId::Sum;
        return true;
    }
    if (equalsIgnoreCase(p, "PRD", 3))
    {
        outId = FunctionId::Prd;
        return true;
    }

    return false;
}

// Tries to parse a Function (e.g. "SUM") OR a Variable (e.g. "X")
// We group them because both start with letters
// NOTE: A function definition implies it is followed by open parenthesis - '('
inline bool tryParseFuncOrVar(const char*& p, Token& outToken, bool& isFunction)
{
    if (!isLetterChar(*p))
        return false;

    // Check if it is a known function name followed by '('
    FunctionId fid;
    size_t len = 0;

    // Peek ahead to see if it matches a function name
    if (parseFunctionId(p, fid, len))
    {
        // Check specifically for the opening parenthesis immediately after the name
        if (p[len] == '(')
        {
            outToken.type = TokenType::Function;
            outToken.funcId = fid;
            outToken.argCount = 0;

            isFunction = true;
            p += len; // Consume the function name (e.g., "SUM"), leave '(' for the parser
            return true;
        }
    }

    // If not a function, it must be a variable (i.e. single char based on requirements)
    outToken.type = TokenType::Variable;
    outToken.varName = static_cast<char>(std::toupper(static_cast<unsigned char>(*p)));

    isFunction = false;
    ++p; // Consume the variable character
    return true;
}