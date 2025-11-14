#include <iostream>
#include <utility>

// Selection Sort
// Time: O(n^2), Spcae: O(1), not stable
template <typename T>
void selectionSort(T* arr, size_t len)
{
    for (size_t i = 0; i + 1 < len; ++i)
    {
        size_t minIndex = i;

        // Find index of the smallest element in the remaining array
        for (size_t j = i + 1; j < len; ++j)
        {
            if (arr[j] < arr[minIndex])        
                minIndex = j;
        }
        
        if (minIndex != i)
            std::swap(arr[i], arr[minIndex]);  
    }
}

int main()
{
    int arr[] = {7, 6, 5, 4, 3, 2, 1};
    size_t arrLen = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, arrLen);

    for (size_t i = 0; i < arrLen; ++i)
        std::cout << arr[i] << " ";
        
    std::cout << '\n';
    return 0;
}