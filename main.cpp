


#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <vector>

#include "arena_and_player_info.h"
#include "get_key.h"
#include "arena_lib.h"
#include "ray_lib.h"
#include "player_lib.h"


#ifdef _WIN32
#include <windows.h>
extern HANDLE hConsole;
#define PRINT_CHAR(x) WriteFile(hConsole, x, 4, NULL, NULL)
#else
#include <unistd.h>
#define PRINT_CHAR(x) fputs(x, stdout) // TODO: Use something faster. 
#endif
#define CLEAR_SCREEN() std::cout<<"\033[H"  
#define HIDE_CURSOR() std::cout<<"\033[?25l"
#define SHOW_CURSOR() std::cout<<"\033[?25h"


void DisplayPlayerView(int *rayHitDistances);

const int numberGraphics = 5;
constexpr const char* graphics[numberGraphics] = {"█", "▌", "▒", "░", ".\0\0"};
int interval = maxRayDistance / numberGraphics; 
int remder = maxRayDistance % numberGraphics;

int main()
{   
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    HIDE_CURSOR();
    char directionOfRotateOrMovement;
    int *rayHitDistances;

    do
    {  
        CLEAR_SCREEN();  
        rayHitDistances = CastRay();
        DisplayPlayerView(rayHitDistances);
        PrintArena();
        directionOfRotateOrMovement = GetKey();
        PlayerMovementFirstPerson(directionOfRotateOrMovement);
        for (int y = 0; y < arenaHeightY; y++)
        {
            for (int x = 0; x < arenaLengthX; x++)
            {
                if (arena[y][x] == 2)
                    arena[y][x] = 0;
            }
        }
    } while (directionOfRotateOrMovement != '1');

    SHOW_CURSOR();
    return 0;
}

void DisplayPlayerView(int *rayHitDistances)
{
    for (int y = 0; y < displayHeightY; y++) 
    {
        for (int x = 0; x < numberRays; x++)
        {
            if (y < rayHitDistances[x] || y > displayHeightY - 1 - rayHitDistances[x]) { PRINT_CHAR(graphics[numberGraphics - 1]); }
            else
            {
                int graphicsIndex = rayHitDistances[x] / interval; 
                if (graphicsIndex >= numberGraphics) graphicsIndex = numberGraphics - 1;
                PRINT_CHAR(graphics[graphicsIndex]);
            }
        }
        putchar('\n');
    }
}
