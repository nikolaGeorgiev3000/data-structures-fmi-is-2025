#pragma once // Engine.hpp

#include "RpnEvaluator.hpp"
#include "ShuntingYard.hpp"

#include <iostream>
#include <string>

constexpr unsigned short MAX_ERROR_BUFF_SIZE = 256;

// Wrapper to track the original ID of an expression
struct PendingExpr
{
    int id;
    Expression expr;
};

class Engine
{
public:
    Engine();

    bool hasPending() const; // Returns true if there are expressions waiting in the queue

    void handleRead(); // Command: 'R' - Read an expression from stdin
    void handleCalc(); // Command: 'C' - Try to calculate the next expression

    void processRemainingInteractive(); // Interactive cleanup at the end of the program
private:
    VarTable _vars;
    std::queue<PendingExpr> _queue;
    int _nextId;
    char _errorBuf[MAX_ERROR_BUFF_SIZE]; // Buffer for error messages
};

// Implementations for 'Engine' class

inline Engine::Engine()
    : _nextId(1)
{
    // Initialize error buffer
    _errorBuf[0] = '\0';
}

inline bool Engine::hasPending() const
{
    return !_queue.empty();
}

inline void Engine::handleRead()
{
    // Use std::string ONLY for reading the line (allowed by requirements)
    std::string line;
    if (!std::getline(std::cin, line))
    {
        std::cerr << "Error: Failed to read from input.\n";
        return;
    }

    if (line.empty())
        return;

    Expression expr;
    if (parseAssignmentLine(line.c_str(), expr, _errorBuf, sizeof(_errorBuf)))
    {
        // Success
        int currentId = _nextId++;
        _queue.push({currentId, expr});
        std::cout << "Expression (" << currentId << ") was read.\n";
    }
    else
    {
        // Syntax error during parsing
        std::cerr << "Error reading expression: " << _errorBuf << "\n";
    }
}

inline void Engine::handleCalc()
{
    if (_queue.empty())
    {
        std::cerr << "Error: 'calc' command received but queue is empty.\n";
        return;
    }

    // Get the front expression
    PendingExpr pending = _queue.front();
    _queue.pop();

    double resultValue = 0.0;

    // Try to evaluate
    // IMPORTANT: evaluateExpression modifies pending.expr.rpn if Partial Evaluation happens
    EvalStatus status = evaluateExpression(pending.expr, _vars, resultValue, _errorBuf, sizeof(_errorBuf));

    switch (status)
    {
    case EvalStatus::Ok:
    {
        // Full success
        _vars.set(pending.expr.varName, resultValue);
        std::cout << "Expression (" << pending.id << ") was calculated. "
                  << "The value of " << pending.expr.varName << " is now " << resultValue << ".\n";
        break;
    }
    case EvalStatus::Postponed:
    {
        // Partial evaluation happened
        // The expression logic inside pending.expr.rpn is now simplified (e.g. from '5*3 + 2 + X' to '17 + X')
        // We push it to the back of the queue
        _queue.push(pending);
        std::cout << "Expression (" << pending.id << ") was postponed.\n";
        break;
    }
    case EvalStatus::Error:
    {
        // Fatal error (e.g. division by zero, etc.) -> Discard expression
        std::cerr << "Error calculating Expression (" << pending.id << "): " << _errorBuf << ". Discarding.\n";
        break;
    }
    }
}

inline void Engine::processRemainingInteractive()
{
    if (_queue.empty())
        return;

    std::cout << "There are " << _queue.size() << " pending expressions.\n";
    std::cout << "Do you want to try to calculate them? (y/n): ";

    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        // We try to process the queue
        // To avoid infinite loops (if A depends on B and B depends on A),
        // we can limit the attempts or just run until queue is empty or no progress is made

        // Try to process as many as possible
        size_t maxIterations = _queue.size() * _queue.size() + 20;
        size_t iterations = 0;

        while (!_queue.empty() && iterations < maxIterations)
        {
            handleCalc();
            iterations++;
        }

        if (!_queue.empty())
        {
            std::cout << "Could not resolve all expressions (circular dependency or missing input).\n";
        }
    }
    else
    {
        std::cout << "Discarding remaining expressions.\n";
    }
}