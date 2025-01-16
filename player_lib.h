#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "arena_and_player_info.h"
#include <cmath>

bool tryMovePlayer(int& playerX, int& playerY, float angle) {
    float rad = to_radian(angle); // Convert angle to radians

    int startX = playerX + 0.5 + playerSpeed * cos(rad);
    int startY = playerY + 0.5 + playerSpeed * sin(rad);
    
    if (arena[startY][startX] == 1) return false; 

    playerX = startX;
    playerY = startY;
    return true;
}


void tryRotatePlayer(float directionOfRotate) 
{
    playerAngle = (static_cast<int>(playerAngle + directionOfRotate) % 360 + 360) % 360;
}

void PlayerMovementFirstPerson(char directionOfMovement) {
    float moveAngle = playerAngle; // Default to forward
    switch (directionOfMovement) {
        case 'w': case 'W': tryMovePlayer(playerPositionX, playerPositionY, moveAngle); break;                       // Forward
        case 's': case 'S': moveAngle += 180; tryMovePlayer(playerPositionX, playerPositionY, moveAngle); break;     // Backward
        case 'a': case 'A': moveAngle -= 90; tryMovePlayer(playerPositionX, playerPositionY, moveAngle); break;      // Left
        case 'd': case 'D': moveAngle += 90; tryMovePlayer(playerPositionX, playerPositionY, moveAngle); break;      // Right
        case 'q': case 'Q': tryRotatePlayer(-45.0f); break;
        case 'e': case 'E': tryRotatePlayer(45.0f); break;
        default: return; // Invalid input, no movement
    }
}

#endif 