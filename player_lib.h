#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "arena_and_player_info.h"
#include <cmath>

static char lastDirection = '\0'; // Для збереження останньої клавіші
static int **savedPlayerDirection = nullptr; // Збережений напрямок руху
static int pathLength = 0;
static int currentIndex = 0;

void deleteSavedPath() {
    if (savedPlayerDirection) {
        for (int i = 0; i < pathLength; i++) {
            delete[] savedPlayerDirection[i];
        }
        delete[] savedPlayerDirection;
        savedPlayerDirection = nullptr;
    }
}

int **calculatePath(char directionOfMovement)
{
    float rad = to_radian(playerAngle);
    double rayPositionY = playerPositionY + 0.5;
    double rayPositionX = playerPositionX + 0.5;
    double rayStepPositionY = sin(rad);
    double rayStepPositionX = cos(rad);
    pathLength = 0;

    for (; pathLength < 100; pathLength++) /* Максимальна довжина шляху 100 */
    {
        rayPositionY += rayStepPositionY;
        rayPositionX += rayStepPositionX;
        int checkY = static_cast<int>(rayPositionY);
        int checkX = static_cast<int>(rayPositionX);

        if (checkX < 0 || checkY < 0 || checkX >= arenaLengthX || checkY >= arenaHeightY || arena[checkY][checkX] == 1)
        {
            break;
        }
    }

    int **path = new int *[pathLength];
    rayPositionY = playerPositionY + 0.5;
    rayPositionX = playerPositionX + 0.5;
    for (int i = 0; i < pathLength; i++)
    {
        path[i] = new int[2];
        path[i][0] = static_cast<int>(rayPositionY);
        path[i][1] = static_cast<int>(rayPositionX);
        rayPositionY += rayStepPositionY;
        rayPositionX += rayStepPositionX;
    }

    currentIndex = 0;
    return path;
}

bool tryMovePlayer(int &playerX, int &playerY, float angle, char directionOfMovement)
{
    if (lastDirection == directionOfMovement && savedPlayerDirection)
    {
        /* Рух по збереженому шляху */
        if (currentIndex >= pathLength || arena[savedPlayerDirection[currentIndex][0]][savedPlayerDirection[currentIndex][1]] == 1)
        {
            deleteSavedPath(); // Очищаємо збережений шлях
            return false;
        }

        playerX = savedPlayerDirection[currentIndex][1];
        playerY = savedPlayerDirection[currentIndex][0];
        currentIndex++;
        return true;
    }
    else
    {
        /* Обчислення нового шляху */
        lastDirection = directionOfMovement;
        deleteSavedPath();
        savedPlayerDirection = calculatePath(directionOfMovement);
    }

    float rad = to_radian(angle);
    int startX = playerX + playerSpeed * cos(rad);
    int startY = playerY + playerSpeed * sin(rad);

    if (startX < 0 || startY < 0 || startX >= arenaLengthX || startY >= arenaHeightY || arena[startY][startX] == 1)
    {
        deleteSavedPath();
        return false;
    }

    playerX = startX;
    playerY = startY;
    return true;
}

void tryRotatePlayer(float directionOfRotate)
{
    playerAngle = static_cast<int>(playerAngle + directionOfRotate) % 360;
    if (playerAngle < 0)
    {
        playerAngle += 360;
    }
}

void PlayerMovementFirstPerson(char directionOfMovement)
{
    int rotationSpeed = 10;
    float moveAngle = playerAngle; /* За замовчуванням - вперед */
    switch (directionOfMovement)
    {
    case 'w':
    case 'W':
        tryMovePlayer(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        break;
    case 's':
    case 'S':
        moveAngle += 180;
        tryMovePlayer(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        break;
    case 'a':
    case 'A':
        moveAngle -= 90;
        tryMovePlayer(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        break;
    case 'd':
    case 'D':
        moveAngle += 90;
        tryMovePlayer(playerPositionX, playerPositionY, moveAngle, directionOfMovement);
        break; 
    case 'q':
    case 'Q':
        tryRotatePlayer(-rotationSpeed);
        break;
    case 'e':
    case 'E':
        tryRotatePlayer(rotationSpeed);
        break;
    default:
        return; /* Неправильне введення, без руху */
    }
}

#endif
