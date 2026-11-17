#include "Battleship.h"
#include <iostream>

int main()
{
    // Execute the main game loop
    ExecuteGameLoop();

    // Pause the console so it doesn't close immediately
    std::cout << "\nPress any key and hit Enter to exit..." << std::endl;
    int iTemp = 0;
    std::cin >> iTemp; // Waits for user input[cite: 48]

    return 0;
}