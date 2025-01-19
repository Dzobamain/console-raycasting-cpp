#include <iostream>
#include <conio.h>
#include <windows.h>


#define KEY_LIST \
    X(W, 'W') \
    X(S, 'S') \
    X(A, 'A') \
    X(D, 'D') \
    X(Q, 'Q') \
    X(E, 'E') \
    X(SPACE, '\x20') \
    X(ENTER, '\n') \
    X(ESCAPE, '\x1b') \


namespace KEYS {
    constexpr int SPACE = VK_SPACE;
    constexpr int ENTER = VK_RETURN;
    constexpr int ESCAPE = VK_ESCAPE;
    constexpr int W = 0x57;
    constexpr int S = 0x53;
    constexpr int A = 0x41;
    constexpr int D = 0x44;
    constexpr int Q = 0x51;
    constexpr int E = 0x45;
}


bool CHECK_KEY(SHORT keyState) {
    return keyState & 0x8000; 
}


const char CheckInput() {
    if (_kbhit()) { 
        _getch();   
        #define X(key, value) if (CHECK_KEY(GetAsyncKeyState(KEYS::key))) return value;
        KEY_LIST
        #undef X
    }
    return '\0';
}

int main() {
    std::cout << "(Space, Enter, Escape)...\n";

    while (true) {
        const char result = CheckInput();
        if (result > 32 && result < 127) {
            std::cout << result;
        }
        else if (result == KEYS::ESCAPE) break; 
    }

    std::cout << "Press any key to exit...\n";
    return 0;
}
