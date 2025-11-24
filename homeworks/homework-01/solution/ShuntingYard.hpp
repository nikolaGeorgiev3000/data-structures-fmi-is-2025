#pragma once // ShuntingYard.hpp

#include "Expression.hpp"
#include "Lexer.hpp"
#include "Utils.hpp"

#include <stack>

// ================================================
//        HELPER HANDLERS (Logic extraction)
// ================================================

// Process operator precedence and push to RPN
inline void processOperatorPrecedence(
    TokenType currentOp,
    std::stack<Token>& opStack,
    std::queue<Token>& outRpn)
{
    while (!opStack.empty())
    {
        TokenType topType = opStack.top().type;

        // Stop if top is not an operator
        if (!isBinaryOperator(topType) && !isUnaryOperator(topType))
            break;

        int precTop = precedence(topType);
        int precNew = precedence(currentOp);
        bool rightAssoc = isRightAssociative(currentOp);

        bool shouldPop = (rightAssoc && precTop > precNew) || (!rightAssoc && precTop >= precNew);

        if (shouldPop)
        {
            outRpn.push(opStack.top());
            opStack.pop();
        }
        else
        {
            break;
        }
    }
}

// Handle ')'
inline bool handleClosingParenthesis(
    std::stack<Token>& opStack,
    std::queue<Token>& outRpn,
    std::stack<int>& argCountStack,
    bool expectOperand,
    char* errorBuf,
    size_t errorBufSize)
{
    while (!opStack.empty() && opStack.top().type != TokenType::LParen)
    {
        outRpn.push(opStack.top());
        opStack.pop();
    }

    if (opStack.empty())
    {
        setError(errorBuf, errorBufSize, "Mismatched parentheses");
        return false;
    }

    opStack.pop(); // Pop '('

    // Check for function call associated with this parenthesis
    if (!opStack.empty() && opStack.top().type == TokenType::Function)
    {
        if (argCountStack.empty())
        {
            setError(errorBuf, errorBufSize, "Internal function arg count error");
            return false;
        }

        Token funTok = opStack.top();
        opStack.pop();

        int count = argCountStack.top();
        argCountStack.pop();

        // Handle 0 argument functions
        // If we expected an operand but got ')' instead, it means we have '()'
        // However, we must ensure it's strictly '()', and not e.g. 'SUM(1;)' error
        if (expectOperand)
        {
            if (count == 1)
            {
                count = 0; // Correctly handle func() with 0 args
            }
            else
            {
                // Handles cases like 'SUM(1; )' -> unexpected closing
                setError(errorBuf, errorBufSize, "Expected argument before ')'");
                return false;
            }
        }

        funTok.argCount = count;
        outRpn.push(funTok);
    }
    else if (expectOperand)
    {
        // Cases like '()' which is not a func call -> invalid empty expression
        setError(errorBuf, errorBufSize, "Empty parentheses '()' are not allowed");
        return false;
    }
    return true;
}

// Handle Function or Variable logic
inline bool handleFuncOrVar(
    const char*& p,
    std::stack<Token>& opStack,
    std::stack<int>& argCountStack,
    std::queue<Token>& outRpn,
    bool& expectOperand,
    char* errorBuf,
    size_t errorBufSize)
{
    Token nameTok;
    bool isFunc = false;

    // Lexer check
    if (!tryParseFuncOrVar(p, nameTok, isFunc))
        return false;

    if (isFunc)
    {
        // Expect '(' immediately
        if (*p != '(')
        {
            setError(errorBuf, errorBufSize, "Expected '(' after function name");
            return false;
        }

        // Setup function structures
        opStack.push(nameTok);

        Token lp;
        lp.type = TokenType::LParen;
        opStack.push(lp);

        argCountStack.push(1); // Assume 1 arg initially

        ++p; // Consume '('
        expectOperand = true;
    }
    else
    {
        // Variable
        outRpn.push(nameTok);
        expectOperand = false;
    }

    return true;
}

// Handle Argument Separator ';'
inline bool handleSeparator(
    const char*& p,
    std::stack<Token>& opStack,
    std::stack<int>& argCountStack,
    std::queue<Token>& outRpn,
    bool& expectOperand,
    char* errorBuf,
    size_t errorBufSize)
{
    if (*p != ';')
        return false;

    // Flush operators until '('
    while (!opStack.empty() && opStack.top().type != TokenType::LParen)
    {
        outRpn.push(opStack.top());
        opStack.pop();
    }

    if (opStack.empty())
    {
        setError(errorBuf, errorBufSize, "Unexpected ';' outside of function parentheses");
        return false;
    }

    if (argCountStack.empty())
    {
        setError(errorBuf, errorBufSize, "Arg count stack empty during argument separation");
        return false;
    }

    argCountStack.top() += 1;

    ++p;
    expectOperand = true;
    return true;
}

// Handle Operators (+, -, *, /, ^)
inline bool handleOperator(
    const char*& p,
    std::stack<Token>& opStack,
    std::queue<Token>& outRpn,
    bool& expectOperand,
    char* errorBuf,
    size_t errorBufSize)
{
    TokenType opType;
    switch (*p)
    {
    case '+':
        opType = expectOperand ? TokenType::UnaryPlus : TokenType::Plus;
        break;
    case '-':
        opType = expectOperand ? TokenType::UnaryMinus : TokenType::Minus;
        break;
    case '*':
        opType = TokenType::Mul;
        break;
    case '/':
        opType = TokenType::Div;
        break;
    case '^':
        opType = TokenType::Pow;
        break;
    default:
        return false; // Not an operator
    }

    processOperatorPrecedence(opType, opStack, outRpn);

    Token opTok;
    opTok.type = opType;
    opStack.push(opTok);

    ++p;
    expectOperand = true;
    return true;
}

// Final cleanup after the loop
inline bool finalizeRpn(
    std::stack<Token>& opStack,
    std::stack<int>& argCountStack,
    std::queue<Token>& outRpn,
    char* errorBuf,
    size_t errorBufSize)
{
    while (!opStack.empty())
    {
        Token t = opStack.top();
        opStack.pop();

        if (t.type == TokenType::LParen)
        {
            setError(errorBuf, errorBufSize, "Mismatched '(' (unclosed parenthesis)");
            return false;
        }

        if (t.type == TokenType::Function)
        {
            if (argCountStack.empty())
            {
                setError(errorBuf, errorBufSize, "Unbalanced function arg count at end");
                return false;
            }
            t.argCount = argCountStack.top();
            argCountStack.pop();
            outRpn.push(t);
        }
        else
        {
            outRpn.push(t);
        }
    }

    if (!argCountStack.empty())
    {
        setError(errorBuf, errorBufSize, "Unbalanced arg counts (internal error)");
        return false;
    }
    return true;
}

// ========================================
//        INFIX TO RPN (CORE PARSER)
// ========================================

inline bool infixToRpn(
    const char* exprPtr,
    std::queue<Token>& outRpn,
    char* errorBuf,
    size_t errorBufSize)
{
    std::stack<Token> opStack;
    std::stack<int> argCountStack;

    bool expectOperand = true;
    const char* p = exprPtr;

    while (*p != '\0' && *p != '\n')
    {
        if (isSpaceChar(*p))
        {
            ++p;
            continue;
        }

        // 1. Number
        Token numTok;
        if (tryParseNumber(p, numTok))
        {
            outRpn.push(numTok);
            expectOperand = false;
            continue;
        }

        // 2. Function or Variable
        // Use a lookahead check to see if it's a letter
        if (isLetterChar(*p))
        {
            if (!handleFuncOrVar(p, opStack, argCountStack, outRpn, expectOperand, errorBuf, errorBufSize))
                return false;
            continue;
        }

        // 3. Parentheses
        if (*p == '(')
        {
            Token t;
            t.type = TokenType::LParen;
            opStack.push(t);
            ++p;
            expectOperand = true;
            continue;
        }
        if (*p == ')')
        {
            if (!handleClosingParenthesis(opStack, outRpn, argCountStack, expectOperand, errorBuf, errorBufSize))
                return false;
            ++p;
            expectOperand = false; // After ')' we behave as if we consumed an operand (e.g. (3)+...)
            continue;
        }

        // 4. Separator
        if (*p == ';')
        {
            if (!handleSeparator(p, opStack, argCountStack, outRpn, expectOperand, errorBuf, errorBufSize))
                return false;
            continue;
        }

        // 5. Operators
        if (handleOperator(p, opStack, outRpn, expectOperand, errorBuf, errorBufSize))
        {
            continue;
        }

        // If we reached here, it's an invalid character
        setError(errorBuf, errorBufSize, "Invalid character in expression");
        return false;
    }

    // Final Cleanup
    return finalizeRpn(opStack, argCountStack, outRpn, errorBuf, errorBufSize);
}

// Parses a line like: VAR = <expression>
inline bool parseAssignmentLine(
    const char* line,
    Expression& outExpr,
    char* errorBuf,
    size_t errorBufSize)
{
    const char* p = line;
    while (isSpaceChar(*p))
        ++p;

    if (!isLetterChar(*p))
    {
        setError(errorBuf, errorBufSize, "Assignment must start with a variable name");
        return false;
    }
    outExpr.varName = static_cast<char>(std::toupper(static_cast<unsigned char>(*p++)));

    while (isSpaceChar(*p))
        ++p;

    if (*p != '=')
    {
        setError(errorBuf, errorBufSize, "Missing '=' in assignment");
        return false;
    }
    ++p;

    outExpr.rpn = std::queue<Token>();
    return infixToRpn(p, outExpr.rpn, errorBuf, errorBufSize);
}