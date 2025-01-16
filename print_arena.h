
#ifndef PRINT_ARENA_H
#define PRINT_ARENA_H

#include "arena_and_player_info.h"

void PrintArena() 
{
    for (int y = 0; y < arenaHeightY; y++) 
    {
        for (int x = 0; x < arenaLengthX; x++) 
        {
            if (arena[y][x] == 1)
                std::cout << "1 ";
            else if (y == playerPositionY && x == playerPositionX)
                std::cout << "P ";
            else if (arena[y][x] == 2 && arena[y][x] != arena[playerPositionY][playerPositionX])
                std::cout << ". "; 
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
}

#endif 