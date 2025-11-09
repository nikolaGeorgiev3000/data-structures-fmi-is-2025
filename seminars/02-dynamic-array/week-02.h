#ifndef WEEK2_H
#define WEEK2_H

#include <iostream>
#include <vector>

namespace Week2 
{
    void task1();
    void task2();
    void task3();

    // Template Vector Print Function
    template <typename T>
    void printVector(const std::vector<T>& v)
    {   
        for (const T& elem : v)
        {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
}

#endif // WEEK2_H