#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "arena_and_player_info.h"
#include <cmath>

static char lastDirection = 0;

// Clear the saved path
void clearPath(int **&playerPath, int &pathLength)
{
    if (playerPath)
    {
        for (int i = 0; i < pathLength; i++)
        {
            delete[] playerPath[i];
        }
        delete[] playerPath;
        playerPath = nullptr;
        pathLength = 0;
    }
}

void movePlayerAlongPath(int &playerX, int &playerY, int angle, char directionOfMovement)
{
    constexpr unsigned maxPathLength = arenaHeightY * arenaLengthX;
    static int **playerPath = nullptr;
    static int pathLength = 0;

    float rad = to_radian(angle);

    if (directionOfMovement != lastDirection)
    {
        clearPath(playerPath, pathLength);
        lastDirection = directionOfMovement;
    }

    // New direction
    if (playerPath == nullptr)
    {
        playerPath = new int *[maxPathLength];

        float currentY = playerY + 0.5;
        float currentX = playerX + 0.5;

        float stepY = sin(rad);
        float stepX = cos(rad);

        for (;pathLength < maxPathLength; ++pathLength)
        {
            currentY += stepY;
            currentX += stepX;

            unsigned gridY = static_cast<unsigned>(currentY);
            unsigned gridX = static_cast<unsigned>(currentX);

            if (arena[gridY][gridX] == 1)
                break;

            playerPath[pathLength] = new int[2];
            playerPath[pathLength][0] = gridY;
            playerPath[pathLength][1] = gridX;
        }

        if (pathLength == 0)
        {
            delete[] playerPath;
            playerPath = nullptr;
        }
    }

    // Player movement along the path and moving the starting position
    if (pathLength > 0)
    {
        playerX = playerPath[0][1];
        playerY = playerPath[0][0];

        int **newPath = new int *[pathLength - 1];
        for (int i = 1; i < pathLength; i++)
        {
            newPath[i - 1] = playerPath[i];
        }

        delete[] playerPath[0];
        delete[] playerPath;

        playerPath = newPath;
        pathLength--;
    }
}



void tryRotatePlayer(float directionOfRotate)
{
    playerAngle = (int)(playerAngle+directionOfRotate) % 360;
}

void PlayerMovementFirstPerson(char directionOfMovement)
{
    float speedOfRotate = 45; // Для себя, если забыла убрать - убери.
    switch (directionOfMovement)
    {
    case 'w':
    case 'W':
        movePlayerAlongPath(playerPositionX, playerPositionY, playerAngle, directionOfMovement);
        // Forward
        break;
    case 's':
    case 'S':
        movePlayerAlongPath(playerPositionX, playerPositionY, playerAngle + 180, directionOfMovement);
        // Backward
        break;
    case 'a':
    case 'A':
        movePlayerAlongPath(playerPositionX, playerPositionY, playerAngle - 90, directionOfMovement);
        // Left
        break;
    case 'd':
    case 'D':
        movePlayerAlongPath(playerPositionX, playerPositionY, playerAngle + 90, directionOfMovement);
        // Right
        break;
    case 'q':
    case 'Q':
        tryRotatePlayer(-speedOfRotate);
        lastDirection = directionOfMovement;
        // Rotate Left
        break;
    case 'e':
    case 'E':
        tryRotatePlayer(speedOfRotate);
        lastDirection = directionOfMovement;
        // Rotate Right
        break;
    default:
        return;
    }
}

#endif
