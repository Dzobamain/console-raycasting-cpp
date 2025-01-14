// arena_and_player_info.h
#ifndef ARENA_AND_PLAYER_INFO_H
#define ARENA_AND_PLAYER_INFO_H

#include <errno.h> // errno
#include <fcntl.h> // open(), O_EVTONLY, O_NONBLOCK
#include <unistd.h> // close()
#include <sys/ioctl.h> // ioctl()

// Арена / Arena
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
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


// Дисплей / Display
const int displayHeightY = 24;
const int displaylLengthX = 80;
char display[displayHeightY][displaylLengthX];

int* GetTerminalSize() // Взято з / Take from https://github.com/sindresorhus/macos-terminal-size
{
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

    int* displaylLengthYAnddisplayHeightX = new int[2];
    displaylLengthYAnddisplayHeightX[0] = ws.ws_col;
    displaylLengthYAnddisplayHeightX[1] = ws.ws_row;

    return displaylLengthYAnddisplayHeightX;
}

// Гравець / Player
int playerPositionY = 2;
int playerPositionX = 2;
int playerSpeed = 1;
float fieldOfView = 90.0f; // Поле зору / Field of view
float playerAngle = 0.0f; // Початковий градус в яку дивиться гравець / Initial angle the player is facing
int maxRayDistance = 10; // Дальність зору / View distance
int numberRays = displaylLengthX;

#endif // ARENA_AND_PLAYER_INFO_H