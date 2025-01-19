// ray_lib.h
#ifndef RAY_LIB_H
#define RAY_LIB_H

#include "arena_and_player_info.h"
#include <cmath>

#define d_currentAngle(pa,i, as) (pa - 45.0f + (i * as))

int* CastRay() 
{   
    int* rayHitDistances = new int[numberRays];
    float angleStep = fieldOfView / (numberRays - 1); 

    for (int i{0}; i < numberRays; ++i) 
    {
        float rad = to_radian(d_currentAngle(playerAngle, i, angleStep)); 

        float rayPositionY = playerPositionY + 0.5;
        float rayPositionX = playerPositionX + 0.5;

        float rayStepPositionY = sin(rad); 
        float rayStepPositionX = cos(rad); 

        for (int d{0}; d < maxRayDistance; d++)
        {
            rayHitDistances[i] = d;

            rayPositionY += rayStepPositionY;
            rayPositionX += rayStepPositionX;

            unsigned checkY = static_cast<unsigned>(rayPositionY);
            unsigned checkX = static_cast<unsigned>(rayPositionX);

            if (checkX >= arenaLengthX || checkY >= arenaHeightY)
                break;

            if (arena[checkY][checkX] == 1) 
                break;
            
            arena[checkY][checkX] = 2; // WTF
        }
    }
    return rayHitDistances;
}

#endif 
