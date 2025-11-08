#include "week-01.h"

// Helper variation function
void combine(const int numberArr[], size_t arrSize, size_t k, 
             size_t startIndex, 
             int currCombination[], size_t combinationSize)
{
    if (combinationSize == k)
    {
        Week1::print(currCombination, combinationSize);
        return;
    }

    // Try every possible next element
    for (size_t i = startIndex; i < arrSize; ++i)
    {
        currCombination[combinationSize] = numberArr[i];
        combine(numberArr, arrSize, k, i + 1, currCombination, combinationSize + 1);
    }
}

// Public wrapper
void combine(const int numberArr[], size_t arrSize, size_t k)
{
    constexpr size_t MAX_SIZE = 10000;
    
    // Argument Safety
    if (k > arrSize || arrSize > MAX_SIZE)
    {
        std::cerr << "Invalid `k` and/or array size.\n";
        return;
    }

    int combination[MAX_SIZE];
    combine(numberArr, arrSize, k, /*startIndex*/0, combination, /*combinationSize*/0);
}

void Week1::task6()
{
    int numbers[] = {3, 2, 1, 5};
    combine(numbers, sizeof(numbers) / sizeof(int), 2); // [4! / (2! * 2!)] = 2 * 3 = 6 combinations
}