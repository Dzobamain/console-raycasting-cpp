// rotate_ray.h
#ifndef ROTATE_RAY_H
#define ROTATE_RAY_H

#include "arena_and_player_info.h"

void RotateRay(char directionOfRotate) 
{
    if (directionOfRotate == 'e') 
        playerAngle -= 10.0f;  // Поворот на X градусов влево / Rotate X degrees to the left
    else if (directionOfRotate == 'r')
        playerAngle += 10.0f;  // Поворот на X градусов вправо / Rotate X degrees to the right

    // Логіка 0-360 градусів / Logic of 0-360 degrees
    if (playerAngle >= 360.0f) playerAngle -= 360.0f;
    if (playerAngle < 0.0f) playerAngle += 360.0f;
}

#endif // ROTATE_RAY_H