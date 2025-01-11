// Console_Raycasting_cpp
// Libraries
#include <iostream>
#include <cmath>
// Header files
#include "GetKey.h"
// █, ▓, ▒, ░

const int arenaHeightY = 8;
const int arenaLengthX = 12;
int arena[arenaHeightY][arenaLengthX] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int playerPositionY = 2;
int playerPositionX = 2;
int playerSpeed = 1;

void PlayerMovement(char directionOfMovement, int movementSpeed);
void PrintArena();

int main()
{
    char playerDirection;

    do
    {
        system("clear");
        PrintArena();
        
        playerDirection = GetKey();
        PlayerMovement(playerDirection, playerSpeed);
    } while (playerDirection != 'q' && playerDirection != 'Q');
}

void PlayerMovement(char directionOfMovement, int movementSpeed)
{
    switch (directionOfMovement)
    {
    case 'w': // Рух в гору / Moving up
    case 'W':
        for (int i = 1; i <= movementSpeed; i++)
        {
            if (playerPositionY - 1 >= 0 && arena[playerPositionY - 1][playerPositionX] != 1)
                playerPositionY--;
            else
                break;
        }
        break;
    case 's': // Рух в низ /  Moving down
    case 'S':
        for (int i = 1; i <= movementSpeed; i++)
        {
            if (playerPositionY + 1 < arenaHeightY && arena[playerPositionY + 1][playerPositionX] != 1)
                playerPositionY++;
            else
                break;
        }
        break;
    case 'd': // рух в вправо / Moving right
    case 'D':
        for (int i = 1; i <= movementSpeed; i++)
        {
            if (playerPositionX + 1 < arenaLengthX && arena[playerPositionY][playerPositionX + 1] != 1)
                playerPositionX++;
            else
                break;
        }
        break;
    case 'a': // рух в вліво / Moving left
    case 'A':
        for (int i = 1; i <= movementSpeed; i++)
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

void PrintArena()
{
    for (int i = 0; i < arenaHeightY; i++)
    {
        for (int j = 0; j < arenaLengthX; j++)
        {
            if (i == playerPositionY && j == playerPositionX)
                std::cout << "P ";
            else if (arena[i][j] == 0)
                std::cout << "  ";
            else
                std::cout << arena[i][j] << " ";
        }
        std::cout << std::endl;
    }
}