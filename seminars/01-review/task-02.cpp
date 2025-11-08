#include "week-01.h"

#include <sstream>
#include <new>


// Reads a C-style string from an input stream
// Returns a dynamically allocated char array or nullptr on error
// Time: O(n), Space: O(n)
char* readCString(std::istream& in) 
{
    int stringLength = 0;
    in >> stringLength;

    // Validate input length
    if (stringLength < 0)
    {
        return nullptr;
    }

    try
    {
        char* resultString = new char[stringLength + 1];

        in.get(); // Consume leftover character after the length
        in.read(resultString, stringLength); // Read exactly `stringLength` characters

        // Check of the string read failed
        if (!in)
        {
            delete[] resultString;
            return nullptr;
        }

        resultString[stringLength] = '\0';
        return resultString;
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
}

// Prints a C-style string safely
void printCString(const char* const cstr)
{
    if (cstr != nullptr)
    {
        std::cout << cstr << '\n';
    }
    else 
    {
        std::cout << "nullptr\n";
    }
}

void Week1::task2() {
    std::cout << "=== Task 2: readCString tests ===\n";

    {
        std::stringstream stream;
        stream << "10 I love c++";
        char* cstring = readCString(stream);
        printCString(cstring);
        delete[] cstring;
    }

    {
        // Negative length
        std::stringstream stream;
        stream << "-3 iam";
        char* cstring = readCString(stream);
        printCString(cstring);
        delete[] cstring;
    }

    {
        // Input shorter than declared length
        std::stringstream stream;
        stream << "12 less chars";
        char* cstring = readCString(stream);
        printCString(cstring);
        delete[] cstring;
    }
    

    std::cout << "\nFun Fact: std::string автоматично управлява динамичната памет,\n"
    << "като използва RAII: заделя памет при инициализация/увеличаване и гарантирано\n"
    << "я освобождава чрез деструктора си при излизане от обхват.\n";
}