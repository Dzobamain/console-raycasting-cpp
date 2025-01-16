// player_movementYX.h
#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "arena_and_player_info.h"

void PlayerMovementYX(char directionOfMovement)
{
    switch (directionOfMovement)
    {
    case 'w': // Рух в гору / Moving up
    case 'W':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionY - 1 >= 0 && arena[playerPositionY - 1][playerPositionX] != 1)
                playerPositionY--;
            else
                break;
        }
        break;
    case 's': // Рух в низ /  Moving down
    case 'S':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionY + 1 < arenaHeightY && arena[playerPositionY + 1][playerPositionX] != 1)
                playerPositionY++;
            else
                break;
        }
        break;
    case 'd': // рух в вправо / Moving right
    case 'D':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionX + 1 < arenaLengthX && arena[playerPositionY][playerPositionX + 1] != 1)
                playerPositionX++;
            else
                break;
        }
        break;
    case 'a': // рух в вліво / Moving left
    case 'A':
        for (int i = 1; i <= playerSpeed; i++)
        {
            if (playerPositionX - 1 >= 0 && arena[playerPositionY][playerPositionX - 1] != 1)
                playerPositionX--;
            else
                break;
        }
        break;
    default:
        //std::cout << "Unknown key sequence!" << std::endl;
        break;
    }
}

#endif // PLAYER_MOVEMENTYX_H