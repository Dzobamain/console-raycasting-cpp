// ray_lib.h
#ifndef RAY_LIB_H
#define RAY_LIB_H

#include "arena_and_player_info.h"
#include <cmath>

void RotateRay(char directionOfRotate) 
{
    if (directionOfRotate == 'q' || directionOfRotate == 'Q') 
        playerAngle -= 10.0f;  // Поворот на X градусов влево / Rotate X degrees to the left
    else if (directionOfRotate == 'e' || directionOfRotate == 'E')
        playerAngle += 10.0f;  // Поворот на X градусов вправо / Rotate X degrees to the right

    // Логіка 0-360 градусів / Logic of 0-360 degrees
    if (playerAngle >= 360.0f) playerAngle -= 360.0f;
    if (playerAngle < 0.0f) playerAngle += 360.0f;
}


int* CastRay() 
{
    int* rayHitDistances = new int[numberRays];
    float angleStep = fieldOfView / (numberRays - 1); 

    for (int i{0}; i < numberRays; i++) 
    {
        float currentAngle = playerAngle - 45.0f + (i * angleStep); 
        double rad = currentAngle * 3.14159265358979323846 / 180.0; 

        double rayPositionY = playerPositionY + 0.5;
        double rayPositionX = playerPositionX + 0.5;

        double rayStepPositionY = sin(rad); 
        double rayStepPositionX = cos(rad); 

        for (int d{0}; d < maxRayDistance; d++)
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
            
            arena[checkY][checkX] = 2; 
        }
    }

    return rayHitDistances;
}

#endif 
