#include "dynarray.hpp"

#include <cassert>
#include <iostream>
#include <string>

struct Tracker
{
    static int constructed;
    static int destroyed;

    int value;

    Tracker(int v = 0) : value(v) { ++constructed; }
    Tracker(const Tracker& other) : value(other.value) { ++constructed; }
    Tracker(Tracker&& other) noexcept : value(other.value)
    {
        other.value = -1;
        ++constructed;
    }

    Tracker& operator=(const Tracker& other)
    {
        value = other.value;
        return *this;
    }

    Tracker& operator=(Tracker&& other) noexcept
    {
        value = other.value;
        other.value = -1;
        return *this;
    }

    ~Tracker() { ++destroyed; }
};

int Tracker::constructed = 0;
int Tracker::destroyed   = 0;

void test_basic_push_pop()
{
    DynArray<int> a;

    assert(a.size() == 0);
    assert(a.capacity() == 0);
    assert(a.empty());

    for (int i = 0; i < 10; ++i)
        a.push_back(i);

    assert(a.size() == 10);
    assert(!a.empty());
    assert(a.front() == 0);
    assert(a.back() == 9);

    int expected = 9;
    while (!a.empty())
    {
        assert(a.back() == expected--);
        a.pop_back();
    }

    assert(a.size() == 0);
}

void test_resize_reserve()
{
    DynArray<int> a;

    a.reserve(8);
    assert(a.capacity() >= 8);
    assert(a.size() == 0);

    a.resize(5); // Default-constructed elements
    assert(a.size() == 5);

    for (std::size_t i = 0; i < a.size(); ++i)
        a[i] = static_cast<int>(i * 10);

    a.resize(10);
    assert(a.size() == 10);

    for (int i = 0; i < 5; ++i)
        assert(a[i] == i * 10);

    a.shrink_to_fit();
    assert(a.capacity() == a.size());
}

void test_copy_move()
{
    DynArray<std::string> a;
    a.push_back("aa");
    a.push_back("bb");
    a.push_back("cc");

    // Copy constructor
    DynArray<std::string> b(a);
    assert(b.size() == a.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        assert(a[i] == b[i]);

    // Copy assignment
    DynArray<std::string> c;
    c = b;
    assert(c.size() == b.size());
    for (std::size_t i = 0; i < c.size(); ++i)
        assert(c[i] == b[i]);

    // Move constructor
    DynArray<std::string> d(std::move(c));
    assert(c.size() == 0);
    assert(d.size() == b.size());

    // Move assignment
    DynArray<std::string> e;
    e = std::move(d);
    assert(d.size() == 0);
    assert(e.size() == b.size());
}

void test_erase_clear()
{
    DynArray<int> a;
    for (int i = 1; i <= 10; ++i)
        a.push_back(i);

    // Erase middle range [2,6) → remove 3,4,5,6
    a.erase(a.cbegin() + 2, a.cbegin() + 6);
    int expected[] = {1,2,7,8,9,10};
    assert(a.size() == 6);
    for (std::size_t i = 0; i < a.size(); ++i)
        assert(a[i] == expected[i]);

    // Erase a single element
    a.erase(a.cbegin() + 2); // remove 7
    int expected2[] = {1,2,8,9,10};
    assert(a.size() == 5);
    for (std::size_t i = 0; i < a.size(); ++i)
        assert(a[i] == expected2[i]);

    a.clear();
    assert(a.size() == 0);
    assert(a.empty());
}

void test_iterators()
{
    DynArray<int> a;
    for (int i = 0; i < 20; ++i)
        a.push_back(i);

    // Begin/end forward iteration
    int x = 0;
    for (auto it = a.begin(); it != a.end(); ++it, ++x)
        assert(*it == x);

    // Range-for
    x = 0;
    for (int v : a)
        assert(v == x++);

    // Const access
    const DynArray<int>& ca = a;
    for (std::size_t i = 0; i < ca.size(); ++i)
        assert(ca[i] == static_cast<int>(i));

    // Reverse iterator sanity check
    int back = 19;
    for (auto rit = a.rbegin(); rit != a.rend(); ++rit, --back)
        assert(*rit == back);
}

void run_all_tests()
{
    test_basic_push_pop();
    test_resize_reserve();
    test_copy_move();
    test_erase_clear();
    test_iterators();
}

int main()
{
    std::cout << "Running DynArray tests..." << std::endl;
    run_all_tests();
    std::cout << "All DynArray tests passed!" << std::endl;
    return 0;
}