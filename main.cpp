// Console_Raycasting_cpp
// Libraries
#include <iostream>
#include <string>
#include <vector>
#include "arena_and_player_info.h"
#include "get_key.h"
#include "arena_lib.h"
#include "player_lib.h"
#include "ray_lib.h"

#include <thread>
#include <chrono>

void DisplayPlayerView(int *rayHitDistances);

int main()
{
    char directionOfRotateOrMovement;
    int *rayHitDistances;

    do
    {
        rayHitDistances = CastRay();
        DisplayPlayerView(rayHitDistances);
        PrintArena();

        directionOfRotateOrMovement = GetKey();

        // Рух гравця / Player movement
        if (directionOfRotateOrMovement == 'w' || directionOfRotateOrMovement == 'W' ||
            directionOfRotateOrMovement == 's' || directionOfRotateOrMovement == 'S' ||
            directionOfRotateOrMovement == 'd' || directionOfRotateOrMovement == 'D' ||
            directionOfRotateOrMovement == 'a' || directionOfRotateOrMovement == 'A')
        {
            PlayerMovementFirstPerson(directionOfRotateOrMovement);
            //PlayerMovementYX(directionOfRotateOrMovement);
        }

        // Поворот променя / Ray rotation
        if (directionOfRotateOrMovement == 'q' || directionOfRotateOrMovement == 'Q' ||
            directionOfRotateOrMovement == 'e' || directionOfRotateOrMovement == 'E')
            RotateRay(directionOfRotateOrMovement);

        for (int y = 0; y < arenaHeightY; y++)
        {
            for (int x = 0; x < arenaLengthX; x++)
            {
                if (arena[y][x] == 2)
                    arena[y][x] = 0;
            }
        }
        system("clear");
    } while (directionOfRotateOrMovement != '1');
}

void DisplayPlayerView(int *rayHitDistances)
{
    // Графіка / Graphics
    const int numberGraphics = 5;
    std::string graphics[numberGraphics] = {"█", "▓", "▒", "░", "."};

    // Обчислюємо кількість чисел, які відповідають кожному символу / Calculating the number of values corresponding to each symbol
    int interval = maxRayDistance / numberGraphics;  // Інтервал для кожного символу
    int remainder = maxRayDistance % numberGraphics; // Залишок, щоб рівномірно розподілити символи

    for (int y = 0; y < displayHeightY; y++)
    {
        for (int x = 0; x < numberRays; x++)
        {
            if (y < rayHitDistances[x]) // Потолок
            {
                std::cout << graphics[numberGraphics - 1];
            }
            else if (y > displayHeightY - 1 - rayHitDistances[x]) // Земля
            {
                std::cout << graphics[numberGraphics - 1];
            }
            else
            {
                // Виводимо відповідний символ графіки
                int graphicsIndex = rayHitDistances[x] / interval; // Визначаємо індекс графіки
                if (graphicsIndex >= numberGraphics)
                    graphicsIndex = numberGraphics - 1; // Обмеження для верхнього символу

                std::cout << graphics[graphicsIndex];
            }
        }
        std::cout << std::endl;
    }
}
