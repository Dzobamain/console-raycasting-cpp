// arena_lib.h
#ifndef ARENA_LIB_H
#define ARENA_LIB_H

#include "arena_and_player_info.h"
#include <iostream>
#include <string>

void PrintArena() 
{
    constexpr const char* TILE_EMPTY = "  ";  
    constexpr const char* TILE_WALL = "# ";  
    constexpr const char* TILE_PLAYER = "P ";  
    constexpr const char* TILE_RAY = ". ";  

    for (int y = 0; y < arenaHeightY; y++) 
    {
        for (int x = 0; x < arenaLengthX; x++) 
        {
            if (arena[y][x] == 1) // Wall
                std::cout << TILE_WALL;
            else if (y == playerPositionY && x == playerPositionX) // Player
                std::cout << TILE_PLAYER;
            else if (arena[y][x] == 2 && arena[y][x] != arena[playerPositionY][playerPositionX]) // Ray
                std::cout << TILE_RAY; 
            else // Empty space
                std::cout << TILE_EMPTY;
        }
        std::cout << std::endl;
    }
}

#endif // ARENA_LIB_H