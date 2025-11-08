#include "week-01.h"

// Helper print method
void Week1::print(const int numberArr[], size_t arrSize)
{
    for (size_t i = 0; i < arrSize; ++i)
    {
        std::cout << numberArr[i] << " ";
    }
    std::cout << std::endl;
}

// Helper permute method
void permute(const int numberArray[], size_t arraySize, 
             bool used[], 
             int currentPermutation[], size_t permutationSize) 
{
    if (permutationSize == arraySize) 
    {
        Week1::print(currentPermutation, permutationSize);
        return;
    }

    for (size_t i = 0; i < arraySize; ++i) 
    {
        if (!used[i]) 
        {
            used[i] = true;
            currentPermutation[permutationSize] = numberArray[i];
            permute(numberArray, arraySize, used, currentPermutation, permutationSize + 1);
            used[i] = false;
        }
    }
}
  
  // Public wrapper
void permute(const int numberArray[], size_t arraySize) 
{
    constexpr size_t MAX_SIZE = 10000;
    if (arraySize > MAX_SIZE) 
    {
        std::cerr << "Week1::permute: size limit exceded!";
        return;
    }
  
    bool used[MAX_SIZE];
    for (size_t i = 0; i < arraySize; ++i) 
    {
        used[i] = false;
    }
  
    int permutation[MAX_SIZE];
    permute(numberArray, arraySize, used, permutation, 0);
}
  
void Week1::task4() 
{
    int numbers[] = {3, 2, 1, 5};
    permute(numbers, sizeof(numbers) / sizeof(int));
}