
#ifndef GET_KEY_H
#define GET_KEY_H

#ifdef _WIN32
#include <conio.h> 
#else
#include <termios.h>  
#include <unistd.h>   
#include <cstdio>     
#endif

char GetKey()
{
#ifdef _WIN32
    
    if (_kbhit()) {
        return _getch();  
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
    return key;
#endif
}

#endif 
