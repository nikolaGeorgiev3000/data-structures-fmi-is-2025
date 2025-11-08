#include "week-01.h"

// Helper variation function
void vary(const int numberArr[], size_t arrSize, size_t k, 
          bool used[], 
          int currVariation[], size_t varSize)
{
    if (varSize == k)
    {
        Week1::print(currVariation, varSize);
        return;
    }

    for (size_t i = 0; i < arrSize; ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            currVariation[varSize] = numberArr[i];
            vary(numberArr, arrSize, k, used, currVariation, varSize + 1);
            used[i] = false;
        }
    }
}

// Public wrapper
void vary(const int numberArr[], size_t arrSize, size_t k)
{
    constexpr size_t MAX_SIZE = 10000;
    
    // Argument Safety
    if (k > arrSize || arrSize > MAX_SIZE)
    {
        std::cerr << "Invalid `k` and/or array size.\n";
        return;
    }

    bool used[MAX_SIZE];
    for (size_t i = 0; i < arrSize; ++i)
    {
        used[i] = false;
    }

    int variation[MAX_SIZE];
    vary(numberArr, arrSize, k, used, variation, 0);
}

void Week1::task5()
{
    int numbers[] = {3, 2, 1, 5};
    vary(numbers, sizeof(numbers) / sizeof(int), 2); // [4! / (4 - 2)!] = 4 * 3 = 12 variations
}