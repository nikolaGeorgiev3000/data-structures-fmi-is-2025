#include <iostream>
#include <cstddef> // size_t

// Merge two sorted segments: arr[0..len1-1] and arr[len1..len1+len2-1]
template <typename T>
void mergeSegments(T* arr, std::size_t len1, T* arr2, std::size_t len2)
{
    T* buffer = new T[len1 + len2];

    std::size_t i = 0, j = 0, k = 0;

    // Merge both halves while both have elements
    while (i < len1 && j < len2)
    {
        if (arr[i] <= arr2[j])        // <= ensures stability
            buffer[k++] = arr[i++];
        else
            buffer[k++] = arr2[j++];
    }

    // Copy remaining from left half
    while (i < len1)
        buffer[k++] = arr[i++];

    // Copy remaining from right half
    while (j < len2)
        buffer[k++] = arr2[j++];

    // Copy back into arr (covers arr1 and arr2)
    for (std::size_t t = 0; t < len1 + len2; ++t)
        arr[t] = buffer[t];

    delete[] buffer;
}

template <typename T>
void naiveMergeSort(T* arr, std::size_t len)
{
    if (len <= 1)
        return;

    std::size_t mid = len / 2;

    naiveMergeSort(arr, mid);
    naiveMergeSort(arr + mid, len - mid);

    mergeSegments(arr, mid, arr + mid, len - mid);
}

int main()
{
    int arr[] = { 9, 6, 5, 8 };
    std::size_t len = sizeof(arr) / sizeof(arr[0]);

    naiveMergeSort(arr, len);

    for (std::size_t i = 0; i < len; ++i)
        std::cout << arr[i] << " ";
}