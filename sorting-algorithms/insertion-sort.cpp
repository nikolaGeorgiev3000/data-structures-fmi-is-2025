#include <iostream>
#include <utility>

// Naive Insertion Sort using swaps
// Time: O(n^2), Space: O(1)

template <typename T>
void naiveInsertionSort(T* arr, size_t len)
{
    for (size_t i = 1; i < len; ++i)
    {
        size_t index = i;
        while (index > 0 && arr[index] < arr[index - 1])
        {
            std::swap(arr[index], arr[index - 1]);
            --index;
        }
    }
}

// Standard Insection Sort using shifting instead of repeated swaps
// Time: O(n^2), Space: O(1)
// Typically faster than the naive version
template <typename T>
void insertionSort(T* arr, size_t len)
{
    for (size_t i = 1; i < len; ++i)
    {
        T element = arr[i];
        size_t index = i;

        // Shift bigger elements to the right
        while (index > 0 && arr[index - 1] > element)
        {
            arr[index] = arr[index - 1];
            --index;
        }

        // Insert element at correct position
        arr[index] = element;
    }
}

int main()
{
    int arr1[] = { 7, 6, 5, 4, 3, 2, 1 };
    int arr2[] = { 7, 6, 5, 4, 3, 2, 1 };

    std::size_t len = sizeof(arr1) / sizeof(arr1[0]);

    naiveInsertionSort(arr1, len);
    std::cout << "Sorted using naiveInsertionSort: ";
    for (std::size_t i = 0; i < len; ++i)
        std::cout << arr1[i] << " ";
    std::cout << "\n";

    insertionSort(arr2, len);
    std::cout << "Sorted using insertionSort:      ";
    for (std::size_t i = 0; i < len; ++i)
        std::cout << arr2[i] << " ";
    std::cout << "\n";

    return 0;
}