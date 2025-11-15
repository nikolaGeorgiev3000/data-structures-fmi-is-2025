#include <iostream>
#include <cassert>
#include <queue>
#include <vector>

// Nerfed game of Exploding Kittens
unsigned int kittens(const std::string& cards, unsigned int players)
{
    assert(players > 0);

    // Deck of cards - top to bottom order
    std::queue<char> deck;
    for (char c : cards)
    {
        deck.push(c);
    }

    // Queue of alive players, 0-based indices
    std::queue<unsigned> alivePlayers;
    for (unsigned i = 0; i < players; ++i)
    {
        alivePlayers.push(i);
    }

    // How many defuse (S) cards each player currently holds
    std::vector<unsigned> defuses(players, 0);

    while (alivePlayers.size() > 1)
    {
        unsigned currentPlayer = alivePlayers.front();
        alivePlayers.pop();

        char currentCard = deck.front();
        deck.pop();

        switch (currentCard)
        {
            case 'O':
                // Ordinary card – nothing happens, player stays alive.
                alivePlayers.push(currentPlayer);
                break;
            case 'S':
                // Player gets a defuse card; card is consumed.
                ++defuses[currentPlayer];
                alivePlayers.push(currentPlayer);
                break;
            case 'B':
                if (defuses[currentPlayer] > 0)
                {
                    // Player uses one defuse, bomb goes to the bottom of the deck.
                    --defuses[currentPlayer];
                    alivePlayers.push(currentPlayer);
                    deck.push(currentCard);
                } 
                // Else player dies & cat-bomb disappears
                break;
            default:
                assert(false && "Unknown card type");
        }
    }

    // Convert 0-based to 1-based player number
    return alivePlayers.front() + 1;
}

int main()
{
    std::cout << "Running kittens tests...\n";

    auto r1 = kittens("BB", 3);
    auto r2 = kittens("SSBB", 3);
    auto r3 = kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5);
    auto r4 = kittens("SOOSBBOOOOSOOOSBOSOOBOSOSOOBOSOSOOB", 7);

    std::cout << "Results: " << r1 << " " 
                             << r2 << " " 
                             << r3 << " " 
                             << r4 << '\n';

    assert(r1 == 3);
    assert(r2 == 2);
    assert(r3 == 1);
    assert(r4 == 3);

    std::cout << "All tests passed!\n";
    return 0;
}