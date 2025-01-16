
#ifndef GET_KEY_H
#define GET_KEY_H

#ifdef _WIN32
#include <conio.h> 
#else
#include <termios.h>  
#include <unistd.h>   
#include <cstdio>     
#endif
    namespace KEYS {
        constexpr int W = 0x57;
        constexpr int S = 0x53;
        constexpr int A = 0x41;
        constexpr int D = 0x44;
        constexpr int Q = 0x51;
        constexpr int E = 0x45;
    }
char GetKey()
{
#ifdef _WIN32
// x-macros для клавиш
#define KEY_LIST \
    X(W, 'w')    \
    X(S, 's')    \
    X(A, 'a')    \
    X(D, 'd')    \
    X(Q, 'q')    \
    X(E, 'e')    \

#define CHECK_KEY(x) (x & 0x8000)

    


    
    if (_kbhit()) {
        if (_getch()){
            #define X(key, value) if (CHECK_KEY(GetAsyncKeyState(KEYS::key))) return value;
            KEY_LIST
            #undef X 
        }
    }
    return '\0';  
#else
    
    struct termios oldt, newt;
    char key;
    
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    key = getchar();  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    switch (key)
    {
        case 'w':
        case 'W':
        case 's':
        case 'S':
        case 'a':
        case 'A':
        case 'd':
        case 'D':
        case 'q':
        case 'Q':
        case 'e':
        case 'E':
        return key;
        default:
        return '\0';
    } 
#endif
}

#endif 
