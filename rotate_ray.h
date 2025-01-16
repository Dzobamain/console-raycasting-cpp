
#ifndef ROTATE_RAY_H
#define ROTATE_RAY_H

#include "arena_and_player_info.h"

void RotateRay(char directionOfRotate) 
{
    if (directionOfRotate == 'q' || directionOfRotate == 'Q') 
        playerAngle -= 10.0f;  
    else if (directionOfRotate == 'e' || directionOfRotate == 'E')
        playerAngle += 10.0f;  

    
    if (playerAngle >= 360.0f) playerAngle -= 360.0f;
    if (playerAngle < 0.0f) playerAngle += 360.0f;
}

#endif 