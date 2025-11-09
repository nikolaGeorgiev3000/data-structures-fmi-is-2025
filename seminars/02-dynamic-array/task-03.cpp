#include "week-02.h"

template <typename T>
std::vector<T> intersection(const std::vector<T>& first, 
                            const std::vector<T>& second)
{
    std::vector<T> result;

    for (const T& candidate : first)
    {
        bool foundInSecond = false;
        for (const T& el : second)
        {
            if (candidate == el)
            {
                foundInSecond = true;
                break;
            }
        }

        // If element is in second, and not already in result, add it
        if (foundInSecond)
        {
            bool alreadyInResult = false;
            for (const T& existing : result)
            {
                if (existing == candidate)
                {
                    alreadyInResult = true;
                    break;
                }
            }

            if (!alreadyInResult)
                result.push_back(candidate);
        }
    }

    return result;
}

void Week2::task3()
{
    std::vector<int> firstVector = {1, 2, 2, 3};
    std::vector<int> secondVector = {3, 2, 3, 6};

    auto intersectedVector = intersection(firstVector, secondVector);
    std::cout << "Intersected vector: ";
    Week2::printVector(intersectedVector); // 2 3
}