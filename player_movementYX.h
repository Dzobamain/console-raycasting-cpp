
#ifndef PLAYER_MOVEMENTYX_H
#define PLAYER_MOVEMENTYX_H

#include "arena_and_player_info.h"

void PlayerMovementYX(char directionOfMovement)
{
    switch (directionOfMovement)
    {
    case 'a': 
    case 'A':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionY - 1 >= 0 && arena[playerPositionY - 1][playerPositionX] != 1)
                playerPositionY--;
            else
                break;
        }
        break;
    case 'd': 
    case 'D':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionY + 1 < arenaHeightY && arena[playerPositionY + 1][playerPositionX] != 1)
                playerPositionY++;
            else
                break;
        }
        break;
    case 'w': 
    case 'W':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionX + 1 < arenaLengthX && arena[playerPositionY][playerPositionX + 1] != 1)
                playerPositionX++;
            else
                break;
        }
        break;
    case 's': 
    case 'S':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionX - 1 >= 0 && arena[playerPositionY][playerPositionX - 1] != 1)
                playerPositionX--;
            else
                break;
        }
        break;
    default:
        
        break;
    }
}

#endif 