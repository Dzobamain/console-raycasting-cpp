#include <iostream>
#include <windows.h>  
#include <string>


int main() {
    
    SetConsoleOutputCP(CP_UTF8);
    std::string str[] = {"\u2588", "\u2580", "\u2591", "\u2592", "."};
    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        std::cout << "Графический символ Unicode: " << str[i] << std::endl;
    }

    return 0;
}
