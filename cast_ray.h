// cast_ray.h
#ifndef CASH_RAY_H
#define CASH_RAY_H

#include "arena_and_player_info.h"
#include <cmath>

int* CastRay() 
{
    int* rayHitDistances = new int[numberRays];
    float angleStep = fieldOfView / (numberRays - 1); // Розподіляємо кути для променів / Distribute angles for the rays

    for (int i = 0; i < numberRays; i++) 
    {
        float currentAngle = playerAngle - 45.0f + (i * angleStep); // Кут для поточного променя / Angle for the current ray
        double rad = currentAngle * M_PI / 180.0; // Переводимо кут в радіани / Convert the angle to radians

        double rayPositionY = playerPositionY + 0.5;
        double rayPositionX = playerPositionX + 0.5;

        double rayStepPositionY = sin(rad); // Крок луча по Y / Ray step along Y
        double rayStepPositionX = cos(rad); // Крок луча по X / Ray step along X

        for (int d = 0; d < maxRayDistance; d++)
        {
            rayHitDistances[i] = d;

            rayPositionY += rayStepPositionY;
            rayPositionX += rayStepPositionX;

            int checkY = (int)rayPositionY;
            int checkX = (int)rayPositionX;

            if (checkX < 0 || checkY < 0 || checkX >= arenaLengthX || checkY >= arenaHeightY)
                break;

            if (arena[checkY][checkX] == 1) 
                break;
            
            arena[checkY][checkX] = 2; // Позначити місце луча / Mark the ray's position
        }
    }

    return rayHitDistances;
}

#endif // CASH_RAY_H