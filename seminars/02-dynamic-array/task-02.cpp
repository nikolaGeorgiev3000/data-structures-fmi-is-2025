#include "week-02.h"

// Returns the Union of two dynamic arrays, without repetitions
// Time: O(n * m), Space: O(n + m)
template <typename T>
std::vector<T> vectorUnion(const std::vector<T>& first, 
                           const std::vector<T>& second)
{
    std::vector<T> result = first;

    for (const T& candidate : second)
    {
        bool exists = false;

        for (const T& existing : result)
        {
            if (existing == candidate)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            result.push_back(candidate);
        }
    }

    return result;
}


void Week2::task2()
{
    std::vector<int> firstVector = {1, 2, 4};
    std::vector<int> secondVector = {4, 5};

    auto unionVector = vectorUnion(firstVector, secondVector);
    std::cout << "Union vector: ";
    Week2::printVector(unionVector);
}