#pragma once // RpnEvaluator.hpp

#include "Expression.hpp"
#include "Utils.hpp"
#include "VarTable.hpp"

#include <cmath> // std::pow
#include <stack>

// =============================
//        DATA STRUCTURES
// =============================

enum class EvalStatus
{
    Ok,
    Postponed,
    Error
};

// Represents an item on the evaluation stack
// It can be either a concrete numeric value OR a symbolic RPN fragment
struct EvalOperand
{
    bool isSymbolic;       // True if it contains variables/unknowns
    double value;          // Valid if !isSymbolic
    std::queue<Token> rpn; // Valid if isSymbolic

    // Constructor for a concrete number
    EvalOperand(double v)
        : isSymbolic(false), value(v)
    {
    }

    // Constructor for a symbolic fragment
    EvalOperand(const std::queue<Token>& tokens)
        : isSymbolic(true), value(0.0), rpn(tokens)
    {
    }

    // Helper to push a single token as symbolic
    EvalOperand(Token t)
        : isSymbolic(true), value(0.0)
    {
        rpn.push(t);
    }
};

// ==================================
//        NUMERIC MATH HELPERS
// ==================================

inline bool computeBinaryNumeric(
    TokenType op,
    double lhs,
    double rhs,
    double& res,
    char* err,
    size_t errSz)
{
    switch (op)
    {
    case TokenType::Plus:
        res = lhs + rhs;
        return true;
    case TokenType::Minus:
        res = lhs - rhs;
        return true;
    case TokenType::Mul:
        res = lhs * rhs;
        return true;
    case TokenType::Div:
        if (rhs == 0.0)
        {
            setError(err, errSz, "Division by zero");
            return false;
        }
        res = lhs / rhs;
        return true;
    case TokenType::Pow:
        res = std::pow(lhs, rhs);
        return true;
    default:
        return false;
    }
}

inline bool computeFunctionNumeric(
    FunctionId fid,
    int count,
    std::stack<double>& st,
    double& res,
    char* err,
    size_t errSz)
{
    // Handle 0 arguments case
    if (count == 0)
    {
        switch (fid)
        {
        case FunctionId::Sum:
            res = 0.0;
            return true;
        case FunctionId::Prd:
            res = 1.0; // The multiplicative identity (neutral element) for product function
            return true;
        default:
            // MIN, MAX, AVG cannot work with 0 arguments
            setError(err, errSz, "Function MIN/MAX/AVG requires at least one argument");
            return false;
        }
    }

    if (count < 0)
    {
        setError(err, errSz, "Function arg count negative (internal error)");
        return false;
    }

    // Standard logic for 1+ arguments
    double acc = st.top();
    st.pop();
    int n = count - 1;

    while (n-- > 0)
    {
        double v = st.top();
        st.pop();
        switch (fid)
        {
        case FunctionId::Min:
            if (v < acc)
                acc = v;
            break;
        case FunctionId::Max:
            if (v > acc)
                acc = v;
            break;
        case FunctionId::Sum:
        case FunctionId::Avg:
            acc += v;
            break;
        case FunctionId::Prd:
            acc *= v;
            break;
        }
    }
    if (fid == FunctionId::Avg)
        acc /= static_cast<double>(count);
    res = acc;
    return true;
}

// =====================================
//        SYMBOLIC MERGING HELPER
// =====================================

// Merges a concrete value or an RPN fragment into a destination queue
inline void appendOperand(std::queue<Token>& dest, const EvalOperand& op)
{
    if (op.isSymbolic)
    {
        std::queue<Token> temp = op.rpn;
        while (!temp.empty())
        {
            dest.push(temp.front());
            temp.pop();
        }
    }
    else
    {
        Token t;
        t.type = TokenType::Number;
        t.numberValue = op.value;
        dest.push(t);
    }
}

// =======================================
//        TOKEN PROCESSING HANDLERS
// =======================================

// 1. Handle Variable
inline void processVariable(
    Token t,
    const VarTable& vars,
    std::stack<EvalOperand>& st)
{
    double val;
    if (vars.get(t.varName, val))
    {
        st.push(EvalOperand(val)); // Known
    }
    else
    {
        st.push(EvalOperand(t)); // Unknown -> Symbolic
    }
}

// 2. Handle Unary Operators (+, -)
inline bool processUnaryOp(
    Token t,
    std::stack<EvalOperand>& st,
    char* err,
    size_t errSz)
{
    if (st.empty())
    {
        setError(err, errSz, "Stack underflow (unary)");
        return false;
    }

    EvalOperand op = st.top();
    st.pop();

    if (!op.isSymbolic)
    {
        if (t.type == TokenType::UnaryMinus)
            op.value = -op.value;
        st.push(op);
    }
    else
    {
        // Append operator to the RPN fragment
        op.rpn.push(t);
        st.push(op);
    }
    return true;
}

// 3. Handle Binary Operators (+, -, *, /, ^)
inline bool processBinaryOp(
    Token t,
    std::stack<EvalOperand>& st,
    char* err,
    size_t errSz)
{
    if (st.size() < 2)
    {
        setError(err, errSz, "Stack underflow (binary)");
        return false;
    }

    EvalOperand rhs = st.top();
    st.pop();
    EvalOperand lhs = st.top();
    st.pop();

    if (!lhs.isSymbolic && !rhs.isSymbolic)
    {
        // Two numbers -> immediate calculation
        double resVal;
        if (!computeBinaryNumeric(t.type, lhs.value, rhs.value, resVal, err, errSz))
            return false;
        st.push(EvalOperand(resVal));
    }
    else
    {
        // Merge: Lhs rpn + Rhs rpn + Operator
        std::queue<Token> newRpn;
        appendOperand(newRpn, lhs);
        appendOperand(newRpn, rhs);
        newRpn.push(t);
        st.push(EvalOperand(newRpn));
    }
    return true;
}

// 4. Handle Functions (MIN, MAX, etc.)
inline bool processFunctionOp(
    Token t,
    std::stack<EvalOperand>& st,
    char* err,
    size_t errSz)
{
    if (st.size() < static_cast<size_t>(t.argCount))
    {
        setError(err, errSz, "Stack underflow (function)");
        return false;
    }

    // Arguments are on stack in reverse order of popping (LIFO)
    // We need to inspect them to see if ANY are symbolic
    // We use a 'temporary stack' to reverse them back to logical order [Arg1, Arg2...]
    std::stack<EvalOperand> orderedArgs;
    bool anySymbolic = false;

    for (int i = 0; i < t.argCount; ++i)
    {
        if (st.top().isSymbolic)
            anySymbolic = true;
        orderedArgs.push(st.top());
        st.pop();
    }

    if (!anySymbolic)
    {
        // All numeric -> Calculate
        std::stack<double> numericStack;
        // Transfer to a stack expected by computeFunctionNumeric
        while (!orderedArgs.empty())
        {
            numericStack.push(orderedArgs.top().value);
            orderedArgs.pop();
        }

        double resVal;
        if (!computeFunctionNumeric(t.funcId, t.argCount, numericStack, resVal, err, errSz))
            return false;

        st.push(EvalOperand(resVal));
    }
    else
    {
        // Symbolic -> Reconstruct RPN
        std::queue<Token> newRpn;
        while (!orderedArgs.empty())
        {
            appendOperand(newRpn, orderedArgs.top());
            orderedArgs.pop();
        }
        newRpn.push(t); // Append function token
        st.push(EvalOperand(newRpn));
    }
    return true;
}

// ==================================
//        MAIN EVALUATION LOOP
// ==================================

inline EvalStatus evaluateRpnLogic(
    const std::queue<Token>& inputRpn,
    const VarTable& vars,
    EvalOperand& result,
    char* errBuf,
    size_t errBufSize)
{
    std::stack<EvalOperand> st;
    std::queue<Token> rpn = inputRpn;

    while (!rpn.empty())
    {
        Token t = rpn.front();
        rpn.pop();

        switch (t.type)
        {
        case TokenType::Number:
            st.push(EvalOperand(t.numberValue));
            break;

        case TokenType::Variable:
            processVariable(t, vars, st);
            break;

        case TokenType::UnaryPlus:
        case TokenType::UnaryMinus:
            if (!processUnaryOp(t, st, errBuf, errBufSize))
                return EvalStatus::Error;
            break;

        case TokenType::Plus:
        case TokenType::Minus:
        case TokenType::Mul:
        case TokenType::Div:
        case TokenType::Pow:
            if (!processBinaryOp(t, st, errBuf, errBufSize))
                return EvalStatus::Error;
            break;

        case TokenType::Function:
            if (!processFunctionOp(t, st, errBuf, errBufSize))
                return EvalStatus::Error;
            break;

        default:
            setError(errBuf, errBufSize, "Unexpected token");
            return EvalStatus::Error;
        }
    }

    if (st.size() != 1)
    {
        setError(errBuf, errBufSize, "Final stack size != 1");
        return EvalStatus::Error;
    }

    result = st.top();
    return EvalStatus::Ok;
}

// Wrapper for the Engine to use
inline EvalStatus evaluateExpression(
    Expression& expr,
    const VarTable& vars,
    double& outValue,
    char* errBuf,
    size_t errBufSize)
{
    // Use a dummy result holder
    EvalOperand result(0.0);

    EvalStatus status = evaluateRpnLogic(expr.rpn, vars, result, errBuf, errBufSize);

    if (status == EvalStatus::Error)
        return EvalStatus::Error;

    if (result.isSymbolic)
    {
        // Partial evaluation occurred: update the expression with simplified RPN
        expr.rpn = result.rpn;
        return EvalStatus::Postponed;
    }
    else
    {
        // Success
        outValue = result.value;
        return EvalStatus::Ok;
    }
}