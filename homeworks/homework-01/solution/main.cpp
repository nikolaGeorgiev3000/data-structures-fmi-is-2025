// main.cpp
#include "Engine.hpp"

int main(int argc, char* argv[])
{
    // 1. Check command line arguments
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <control_string>\n";
        std::cerr << "Example: " << argv[0] << " RRRCCCC\n";
        return 1;
    }

    const char* controlString = argv[1];
    Engine engine;

    // 2. Process the control string
    for (int i = 0; controlString[i] != '\0'; ++i)
    {
        char cmd = controlString[i];

        if (cmd == 'R' || cmd == 'r')
        {
            engine.handleRead();
        }
        else if (cmd == 'C' || cmd == 'c')
        {
            engine.handleCalc();
        }
        else
        {
            std::cerr << "Warning: Unknown command '"
                      << cmd
                      << "' in control string. Skipping.\n";
        }
    }

    // 3. Handle pending expressions (if any)
    if (engine.hasPending())
        engine.processRemainingInteractive();

    return 0;
}