#include "week-01.h"

// Helper palindrome function
bool isPalindrome(const std::string& str, unsigned symmetricOffset)
{
    // Base case (0 or 1 characters are always palindromes)
    if (str.length() - 2 * symmetricOffset < 2)
    {
        return true;
    }

    // Compare symmetric characters
    char start = str[symmetricOffset];
    char end = str[str.length() - 1 - symmetricOffset];

    // Recursive step
    return (start == end) && isPalindrome(str, symmetricOffset + 1);
}

// Public wrapper
bool isPalindrome(const std::string& str)
{  
    return isPalindrome(str, 0);
}

void Week1::task3()
{

    std::cout << "=== Task 3: Palindrome Check ===\n";

    std::string str;
    std::cout << "Enter a string to check: ";
    std::cin >> str;
        
    std::cout << "Your string is " << (isPalindrome(str) ? "" : "not ") << "a palindrome.\n";
}