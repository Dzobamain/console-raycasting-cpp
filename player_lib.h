// player_movementYX.h
#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "arena_and_player_info.h"
#include <cmath>

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
        // std::cout << "Unknown key sequence!" << std::endl;
        break;
    }
}

void PlayerMovementFirstPerson(char directionOfMovement)
{
    switch (directionOfMovement)
    {
    case 'w': // Рух вперед / Move Forward
    case 'W':
    {
        double rad = playerAngle * M_PI / 180.0; // Переводимо кут в радіани / Convert the angle to radians

        double startPositionY = playerPositionY + 0.5;
        double startPositionX = playerPositionX + 0.5;

        double playerStepPositionY = sin(rad); // Крок гравця по Y / Player step along Y
        double playerStepPositionX = cos(rad); // Крок гравця по X / Player step along X

        startPositionY += playerStepPositionY;
        startPositionX += playerStepPositionX;

        if (arena[(int)startPositionY][(int)startPositionX] == 1)
            break;
        
        playerPositionY = (int)startPositionY;
        playerPositionX = (int)startPositionX;
        break;
    }
    case 's':
    case 'S':
    {
        double rad = playerAngle * M_PI / 180.0; // Переводимо кут в радіани / Convert the angle to radians

        double startPositionY = playerPositionY + 0.5;
        double startPositionX = playerPositionX + 0.5;

        double playerStepPositionY = sin(rad); // Крок гравця по Y / Player step along Y
        double playerStepPositionX = cos(rad); // Крок гравця по X / Player step along X

        startPositionY -= playerStepPositionY;
        startPositionX -= playerStepPositionX;

        if (arena[(int)startPositionY][(int)startPositionX] == 1)
            break;
        
        playerPositionY = (int)startPositionY;
        playerPositionX = (int)startPositionX;
        break;
    }
    case 'a':
    case 'A':
    {
        double rad = (playerAngle + 90) * M_PI / 180.0; // Переводимо кут в радіани / Convert the angle to radians

        double startPositionY = playerPositionY + 0.5;
        double startPositionX = playerPositionX + 0.5;

        double playerStepPositionY = sin(rad); // Крок гравця по Y / Player step along Y
        double playerStepPositionX = cos(rad); // Крок гравця по X / Player step along X

        startPositionY -= playerStepPositionY;
        startPositionX -= playerStepPositionX;

        if (arena[(int)startPositionY][(int)startPositionX] == 1)
            break;
        
        playerPositionY = (int)startPositionY;
        playerPositionX = (int)startPositionX;
        break;
    }
    case 'd':
    case 'D':
    {
        double rad = (playerAngle - 90) * M_PI / 180.0; // Переводимо кут в радіани / Convert the angle to radians

        double startPositionY = playerPositionY + 0.5;
        double startPositionX = playerPositionX + 0.5;

        double playerStepPositionY = sin(rad); // Крок гравця по Y / Player step along Y
        double playerStepPositionX = cos(rad); // Крок гравця по X / Player step along X

        startPositionY -= playerStepPositionY;
        startPositionX -= playerStepPositionX;

        if (arena[(int)startPositionY][(int)startPositionX] == 1)
            break;
        
        playerPositionY = (int)startPositionY;
        playerPositionX = (int)startPositionX;
        break;
    }
    default:
        break;
    }
}

#endif // PLAYER_MOVEMENTYX_H