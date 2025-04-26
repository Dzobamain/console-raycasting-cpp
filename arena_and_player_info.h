/*
Creation of the arena and its levels
Information about the player, the arena, and where to display it.

arena_and_player_info.h
*/

#ifndef ARENA_AND_PLAYER_INFO_H
#define ARENA_AND_PLAYER_INFO_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>  
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#else
#include <errno.h>    
#include <fcntl.h>    
#include <unistd.h>   
#include <sys/ioctl.h> 

#endif

const int arenaHeightY = 20;
const int arenaLengthX = 20;
int arena[arenaHeightY][arenaLengthX] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


int* GetTerminalSize();
const int displayHeightY = GetTerminalSize()[1] - /* mini map */ arenaHeightY - /* input line */ 1;
const int displayLengthX = GetTerminalSize()[0];

int* GetTerminalSize() {
    int* terminalSize = new int[2];

#ifdef _WIN32

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to get console handle." << std::endl;
        return nullptr;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
        return nullptr;
    }
    
    SetConsoleMode(hConsole, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(CP_UTF8);

    #ifdef _DEBUG
    terminalSize[0] = 1000;
    terminalSize[1] = 1000;
    #else
    terminalSize[0] = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
    terminalSize[1] = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; 
    #endif

#else
    
    int tty_fd = open("/dev/tty", O_EVTONLY | O_NONBLOCK);
    if (tty_fd == -1) {
        std::cerr << "Opening `/dev/tty` failed (" << errno << "): " << strerror(errno) << std::endl;
        return nullptr;
    }

    struct winsize ws;
    int result = ioctl(tty_fd, TIOCGWINSZ, &ws);
    close(tty_fd);

    if (result == -1) {
        std::cerr << "Getting the size failed (" << errno << "): " << strerror(errno) << std::endl;
        return nullptr;
    }

    terminalSize[0] = ws.ws_col; 
    terminalSize[1] = ws.ws_row; 
#endif

    return terminalSize;
}

#define PI 3.14159265358979323846
#define to_radian(x) (x * PI / 180.0)
int playerPositionY = 2;
int playerPositionX = 2;
int playerSpeed = 1;
float fieldOfView = 90.0f; 
float playerAngle = 0.0f;
int maxRayDistance = 10; 
int numberRays = displayLengthX;

#endif 
