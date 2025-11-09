#include "week-02.h"

// Appends the elements of two dynamic arrays
// Time: O(n + m), Space: O(n + m)
template <typename T>
std::vector<T> append(const std::vector<T>& first, 
                      const std::vector<T>& second)
{
    std::vector<T> result;

    result.reserve(first.size() + second.size()); // Avoid Reallocations

    for (const T& elem : first)
    {
        result.push_back(elem);
    }

    for (const T& elem : second)
    {
        result.push_back(elem);
    }

    /* Optional:
    std::vector<T> result = first;
    result.insert(result.end(), second.begin(), second.end());
    */
    
    return result;
}

void Week2::task1()
{  
    std::vector<int> firstVector = {1, 2, 3};
    std::vector<int> secondVector = {4, 5, 6};

    auto appendedVector = append(firstVector, secondVector);
    std::cout << "Appended vector: ";
    Week2::printVector(appendedVector);
}