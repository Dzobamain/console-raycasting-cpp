


#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <vector>

#include "arena_and_player_info.h"
#include "get_key.h"
#include "print_arena.h"
#include "player_movementYX.h"
#include "cast_ray.h"
#include "rotate_ray.h"

#ifdef _WIN32
#include <windows.h>
extern HANDLE hConsole;
#define PRINT_CHAR(x) fputs(x, stdout)
#define CLEAR_SCREEN() std::cout<<"\033[H"  
#else
#include <unistd.h>
#define PRINT_CHAR(x) fputs(x, stdout)
#define CLEAR_SCREEN() std::cout<<"\033[H"  
#endif

void DisplayPlayerView(int *rayHitDistances);

const int numberGraphics = 5;
const char* graphics[numberGraphics] = {"█", "▌","▒", "░", "."};
int interval = maxRayDistance / numberGraphics; 
int remder = maxRayDistance % numberGraphics; 


int main()
{   
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    std::cout<<"\033[?25l";
    char directionOfRotateOrMovement;
    int *rayHitDistances;

    do
    {  
        
        CLEAR_SCREEN();  
        
        
        rayHitDistances = CastRay();
        DisplayPlayerView(rayHitDistances);
        
        
        PrintArena();

        
        directionOfRotateOrMovement = GetKey();

        
        if (directionOfRotateOrMovement == 'w' || directionOfRotateOrMovement == 'W' ||
            directionOfRotateOrMovement == 's' || directionOfRotateOrMovement == 'S' ||
            directionOfRotateOrMovement == 'd' || directionOfRotateOrMovement == 'D' ||
            directionOfRotateOrMovement == 'a' || directionOfRotateOrMovement == 'A')
            PlayerMovementYX(directionOfRotateOrMovement);

        
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

    } while (directionOfRotateOrMovement != '1');  

    
    CLEAR_SCREEN();  
}

void DisplayPlayerView(int *rayHitDistances)
{
    for (int y = 0; y < displayHeightY; y++) 
    {
        for (int x = 0; x < numberRays; x++) 
        {
            if (y < rayHitDistances[x] || y > displayHeightY - 1 - rayHitDistances[x]) 
            {
                PRINT_CHAR(graphics[numberGraphics - 1]);
            }
            else 
            {
                
                int graphicsIndex = rayHitDistances[x] / interval; 
                if (graphicsIndex >= numberGraphics) 
                    graphicsIndex = numberGraphics - 1; 

                PRINT_CHAR(graphics[graphicsIndex]);
            }
        }
        putchar('\n');
    }
}
