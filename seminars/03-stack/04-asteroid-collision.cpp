#include <iostream>
#include <vector>


// Resolves all asteroid collisions & returns the final state
// Time: O(n); Space: O(n)
std::vector<int> asteroidCollision(std::vector<int>& asteroids)
{
    std::vector<int> st; // Using the vector as a stack

    for (int a : asteroids)
    {
        bool destroyed = false;

        // Collision only occurs when prev. ast. moves right & curr. ast. moves left
        while (!st.empty() && st.back() > 0 && a < 0)
        {
            int top = st.back();

            if (top < -a)
            {
                st.pop_back(); // Current asteroid is bigger, previous explodes
            } 
            else if (top == -a)
            {
                st.pop_back(); 
                destroyed = true; // Both explode
                break;
            } 
            else
            {
                destroyed = true; // Prev. is bigger, current explodes  
                break;
            }
            
        }
        if (!destroyed)
        {
            st.push_back(a);
        }
    }
    
    return st;
}

// Helper vector print function
template <typename T>
void printVector(const std::vector<T>& v)
{
    std::cout << "Vector: ";
    for (T x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main()
{
    // Test asteroids
    std::vector<int> test1 = {5, 10, -5};
    std::vector<int> test2 = {8, -8};
    std::vector<int> test3 = {10, 2, -5};
    std::vector<int> test4 = {3, 5, -6, 2, -1, 4};

    printVector(asteroidCollision(test1)); // [5, 10]
    printVector(asteroidCollision(test2)); // []
    printVector(asteroidCollision(test3)); // [10]
    printVector(asteroidCollision(test4)); // [-6, 2, 4]

    return 0;
}