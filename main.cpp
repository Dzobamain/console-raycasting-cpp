// Console_Raycasting_cpp
// Libraries
#include <iostream>
// Header files
#include "arena_and_player_info.h"
#include "get_key.h"
#include "print_arena.h"
#include "player_movementYX.h"
#include "cast_ray.h"
#include "rotate_ray.h"
// █, ▓, ▒, ░

int main()
{
    char directionOfRotateOrMovement;
    int* rayHitDistances;

    do 
    {
        //system("clear");
        rayHitDistances = CastRay();
        PrintArena();
        
        directionOfRotateOrMovement = GetKey();

        // Рух гравця / Player movement
        if (directionOfRotateOrMovement == 'w' || directionOfRotateOrMovement == 'W' || 
            directionOfRotateOrMovement == 's' || directionOfRotateOrMovement == 'S' ||
            directionOfRotateOrMovement == 'd' || directionOfRotateOrMovement == 'D' || 
            directionOfRotateOrMovement == 'a' || directionOfRotateOrMovement == 'A')
            PlayerMovementYX(directionOfRotateOrMovement);

        // Поворот променя / Ray rotation
        if (directionOfRotateOrMovement == 'e' || directionOfRotateOrMovement == 'r')
            RotateRay(directionOfRotateOrMovement);

        // Очищаємо арену від старих слідів луча
        for (int y = 0; y < arenaHeightY; y++)
        {
            for (int x = 0; x < arenaLengthX; x++) 
            {
                if (arena[y][x] == 2)
                    arena[y][x] = 0;
            }
        }
    } while (directionOfRotateOrMovement != 'q' && directionOfRotateOrMovement != 'Q');
}