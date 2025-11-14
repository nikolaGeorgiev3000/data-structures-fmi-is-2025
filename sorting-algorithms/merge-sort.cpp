#include <iostream>
#include <cstddef>

// Merge 2 sorted subarrays: [firstArr] & [secondArr]
template <typename T>
void mergeArrays(T* firstArr, size_t firstSize,
                 T* secondArr, size_t secondSize,
                 T* resultArr)
{
    size_t i = 0, j = 0, k = 0;

    while (i < firstSize && j < secondSize)
    {
        if (firstArr[i] <= secondArr[j]) // <= ensures stability
            resultArr[k++] = firstArr[i++];
        else
            resultArr[k++] = secondArr[j++];
    }

    while (i < firstSize)
        resultArr[k++] = firstArr[i++];

    while (j < secondSize)
        resultArr[k++] = secondArr[j++];
}

template <class T>
void mergeSortRec(T* arr, size_t size, T* buffer)
{
    if (size <= 1)
        return;

    size_t mid = size / 2;

    // Sort left half
    mergeSortRec(arr, mid, buffer);

    // Sort right half
    mergeSortRec(arr + mid, size - mid, buffer + mid);

    // Merge halves into buffer
    mergeArrays(arr, mid, arr + mid, size - mid, buffer);

    // Copy merged result back into original array
    for (size_t i = 0; i < size; ++i)
        arr[i] = buffer[i];
}

template <class T>
void mergeSort(T* arr, size_t size)
{
    if (size < 2)
        return;

    T* buffer = new T[size];
    mergeSortRec(arr, size, buffer);
    delete[] buffer;
}

int main()
{
    int arr[] = {15, 14, 13, 12, 11, 30, 90, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr size_t SIZE = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, SIZE);

    for (size_t i = 0; i < SIZE; ++i)
        std::cout << arr[i] << " ";
}
