#include "week-01.h"

// Template swap function using pointers & references
// Time Complexity: O(1), Space Complexity: O(1)
template <typename T>
void swap(T* lhs, T* rhs)
{
    T temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

template <typename T>
void swap(T& lhs, T& rhs)
{
    T temp = lhs;
    lhs = rhs;
    rhs = temp;
}

void Week1::task1()
{
    int a = 0, b = 0;
    std::cout << "Enter two integers:\t";
    std::cin >> a >> b;
    std::cout << "Integers before swap:\t" << a << ", " << b;
    swap(&a, &b);
    std::cout << "\nIntegers after swap using pointers:\t" << a << ", " << b << std::endl;

    std::string c, d;
    std::cout << "Enter string 1:\t";
    std::cin >> c;
    std::cout << "Enter string 2:\t";
    std::cin >> d;
    std::cout << "Strings before swap:\t" << c << ", " << d;
    swap(c, d);
    std::cout << "\nStrings after swap using references:\t" << c << ", " << d << std::endl; 
}