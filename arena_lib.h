#ifndef ARENA_LIB_H
#define ARENA_LIB_H

#include <iostream>
#include <string>

#include "arena_and_player_info.h"

void PrintArena() 
{
    const char* TILE_EMPTY = "  ";  
    const char* TILE_WALL = "# ";  
    const char* TILE_PLAYER = "P ";  
    const char* TILE_RAY = ". ";  

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

#endif