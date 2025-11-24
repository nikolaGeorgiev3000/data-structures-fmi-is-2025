# Homework 1: Expression Evaluator Engine

This homework implements a C++ system for parsing and evaluating mathematical expressions using the **Shunting-yard algorithm** and **Reverse Polish Notation (RPN)**. It is designed to handle **variables**, **n-ary functions**, and **partial evaluation** (simplification of expressions with unknown variables).

## Features

- **Control Flow:** Driven by a command-line control string (e.g., `RRCC`) executing **Read** (`R`) and **Calculate** (`C`) operations.
- **Arithmetic:** Binary operators (`+`, `-`, `*`, `/`, `^`), Unary operators (`+`, `-`), and Parentheses.
- **Functions:** `MIN`, `MAX`, `AVG`, `SUM`, `PRD`. Supports arbitrary argument counts (including 0 arguments **where mathematically valid**).
- **Variables:** `A-Z` (case-insensitive).
- **Partial Evaluation:** If a variable value is missing during calculation, the system does not fail. Instead, it simplifies the RPN expression by merging known constants and retaining unknown symbols, then postpones the task to the end of the queue.

## File Structure

The solution follows a flat structure with inline implementations (_header-only_ style) for ease of compilation.

- `main.cpp`: Entry point. Parses the control string and drives the Engine.
- `Engine.hpp`: Manages the expression queue, variable state (`VarTable`), and I/O logic.
- `ShuntingYard.hpp`: Core parser converting Infix notation to RPN. Handles operator precedence and associativity.
- `RpnEvaluator.hpp`: Stack-based evaluator. Handles both numeric computation and symbolic reconstruction (for partial evaluation).
- `Lexer.hpp` & `Token.hpp`: Tokenization logic and data structures.
- `Expression.hpp`: Wrapper for a parsed expression (Variable Name + RPN Queue).
- `VarTable.hpp`: Simple array-based lookup table for variables `A-Z`.
- `Utils.hpp`: Helper functions for string manipulation and error handling.

## Build & Run

**Requirements:** Standard C++17 compiler. No external libraries used (standard STL only).

### Compilation

```bash
g++ -std=c++17 main.cpp -o homework-01
```

### Usage

Run the executable providing the control string as an argument:

```bash
./homework-01 RRRRCCCCRCC
```

Then provide the expressions **successively** via standard input as requested by the program. Example input:

```bash
x = 2 * SUM(x; 4.5+2*y; 1.5)
y = 5+6 * -2
z = SUM(MIN(1; 2; 3); SUM(1))
x = 5*6
y = 2 * x
```

## Implementation Details

- **Partial Evaluation:** The most complex feature. If a variable is missing during evaluation, the system switches to **"Symbolic Mode"**. It merges the RPN fragments of the operands and the operator into a new, simplified RPN sequence, which is then stored back in the queue (_Postponed_).

- **Zero-Argument Functions:** Handled explicitly. `SUM()` evaluates to **0**, `PRD()` to **1**. `MIN`, `MAX`, and `AVG` return runtime errors as they are mathematically undefined for empty sets.

- **Compliance:** The solution strictly adheres to the restriction of using only `std::stack`, `std::queue`, and `std::string` (_strictly for input reading_). No `<algorithm>` (e.g., `std::swap` is avoided) or dynamic memory allocation (`new`/`delete`) is used.

## Author

Nikola Georgiev
