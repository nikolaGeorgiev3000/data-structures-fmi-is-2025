#include <iostream>
#include <utility>
#include <cstddef>

// Lomuto partition scheme
// Returns the final index of the pivot
template <typename T>
std::size_t partitionLomuto(T* arr, std::size_t len)
{
    T pivot = arr[len - 1];        // Pivot = last element
    std::size_t i = 0;             // Place for the next smaller element

    for (std::size_t j = 0; j + 1 < len; ++j)
    {
        if (arr[j] < pivot)
        {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    // Place pivot in its final position
    std::swap(arr[i], arr[len - 1]);
    return i;
}

template <typename T>
void quickSort(T* arr, std::size_t len)
{
    if (len <= 1)
        return;

    std::size_t pivotIndex = partitionLomuto(arr, len);

    // Sort left side: elements < pivot
    quickSort(arr, pivotIndex);

    // Sort right side: elements > pivot
    quickSort(arr + pivotIndex + 1, len - pivotIndex - 1);
}

int main()
{
    int arr[] = { 15, 14, 13, 12, 11, 30, 90, 8, 7, 6, 5, 4, 3, 2, 1 };
    constexpr std::size_t SIZE = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, SIZE);

    for (std::size_t i = 0; i < SIZE; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}