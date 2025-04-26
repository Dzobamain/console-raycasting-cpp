/*
All interactions with the player from a first-person perspective, such as movement.

player_lib.h
*/

#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include <cmath>

#include "arena_and_player_info.h"

static char lastDirection = 0;

bool isMovePossible(int x, int y)
{
    return (x >= 0 && y >= 0 && x < arenaLengthX && y < arenaHeightY && arena[y][x] != 1);
}

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

void movePlayerAlongPath(int &playerX, int &playerY, float angle, char directionOfMovement)
{
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
        int maxPathLength = arenaHeightY * arenaLengthX;
        playerPath = new int *[maxPathLength];
        int currentPathIndex = 0;

        double currentY = playerY + 0.5;
        double currentX = playerX + 0.5;

        double stepY = sin(rad);
        double stepX = cos(rad);

        while (currentPathIndex < maxPathLength)
        {
            currentY += stepY;
            currentX += stepX;

            int gridY = static_cast<int>(currentY);
            int gridX = static_cast<int>(currentX);

            if (!isMovePossible(gridX, gridY))
                break;

            playerPath[currentPathIndex] = new int[2];
            playerPath[currentPathIndex][0] = gridY;
            playerPath[currentPathIndex][1] = gridX;
            currentPathIndex++;
        }

        pathLength = currentPathIndex;

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

void tryRotatePlayer(float directionOfRotate, char directionOfMovement)
{
    playerAngle = (static_cast<int>(playerAngle + directionOfRotate) % 360 + 360) % 360;
    lastDirection = directionOfMovement;
}

void PlayerMovementFirstPerson(char directionOfMovement)
{
    float speedOfRotate = 10;
    float moveAngle = playerAngle;
    switch (directionOfMovement)
    {
    case 'w':
    case 'W':
        movePlayerAlongPath(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        // Forward
        break;
    case 's':
    case 'S':
        moveAngle += 180;
        movePlayerAlongPath(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        // Backward
        break;
    case 'a':
    case 'A':
        moveAngle -= 90;
        movePlayerAlongPath(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        // Left
        break;
    case 'd':
    case 'D':
        moveAngle += 90;
        movePlayerAlongPath(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        // Right
        break;
    case 'q':
    case 'Q':
        tryRotatePlayer(-speedOfRotate, directionOfMovement);
        // Rotate Left
        break;
    case 'e':
    case 'E':
        tryRotatePlayer(speedOfRotate, directionOfMovement);
        // Rotate Right
        break;
    default:
        return;
    }
}

#endif
