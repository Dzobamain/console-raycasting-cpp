// get_key.h
#ifndef GET_KEY_H
#define GET_KEY_H

// for macOS
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

#endif // GET_KEY_H