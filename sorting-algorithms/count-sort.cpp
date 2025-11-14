#include <iostream>
#include <string>

struct Student
{
    std::string name;
    int grade; // Assumed in [2, 6]
};

void countSortByGrade(Student* arr, size_t len)
{
    if (len == 0)
        return;

    constexpr int MIN_GRADE = 2;
    constexpr int MAX_GRADE = 6;
    constexpr size_t GRADES_VALUES_COUNT = MAX_GRADE - MIN_GRADE + 1;

    // count[i] = how many students with grade (MIN_GRADE + i)
    size_t count[GRADES_VALUES_COUNT] = {0};

    // 1) Count occurrences
    for (size_t i = 0; i < len; ++i)
    {
        int g = arr[i].grade;
        count[g - MIN_GRADE]++;
    }

    // 2) Prefix sums - positions
    for (size_t i = 1; i < GRADES_VALUES_COUNT; ++i)
        count[i] += count[i - 1];

    // 3) Build stable result (iterate from right to left)
    Student* result = new Student[len];

    for (size_t i = len; i > 0;)
    {
        --i;
        const Student& s = arr[i];
        size_t idx = --count[s.grade - MIN_GRADE];
        result[idx] = s; // Stable: later elements go to higher indices
    }

    // 4) Copy back
    for (size_t i = 0; i < len; ++i)
    {
        arr[i] = result[i];
    }

    delete[] result;   
}

int main()
{
    Student arr[] = {
        {"Petur",    4},
        {"Ivan",     6},
        {"Alex",     4},
        {"Vladimir", 5},
        {"Katerina", 5}
    };

    std::size_t n = sizeof(arr) / sizeof(arr[0]);
    countSortByGrade(arr, n);

    for (std::size_t i = 0; i < n; ++i)
        std::cout << "Name: " << arr[i].name
                  << ", grade: " << arr[i].grade << '\n';

    return 0;
}