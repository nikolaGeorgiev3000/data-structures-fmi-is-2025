#include <iostream>
#include <utility>

template <typename T>
void bubbleSort(T* arr, unsigned len)
{
    if (len < 2) return; // Already sorted or empty

    unsigned end = len - 1;

    while (end > 0)
    {
        unsigned lastSwappedIndex = 0;

        for (unsigned j = 0; j < end; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                lastSwappedIndex = j;
            }
        }

        // Move boundary to last swap position
        end = lastSwappedIndex;

        // No swaps - already sorted
        if (lastSwappedIndex == 0)
            break;
    }
}

int main()
{
    int arr[] = {7, 6, 5, 4, 3, 2, 1};
    int arrLen = sizeof(arr) / sizeof(int);

    bubbleSort(arr, arrLen);

    for (int i = 0; i < arrLen; i++) 
        std::cout << arr[i] << " ";

    return 0;
}