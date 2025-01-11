// GetKey.h
#ifndef GETKEY_H
#define GETKEY_H

#include <termios.h> 
#include <unistd.h> 
#include <cstdio>


char GetKey()
{
    struct termios oldt, newt;
    char key;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    key = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return key;
}

#endif // GETKEY_H