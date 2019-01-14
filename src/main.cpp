#define GL3W_IMPLEMENTATION

#include <gl3w.h>

// stlib
#include <chrono>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;

// Global
const int width = 600;
const int height = 400;
const char *title = "Panda Express";

// Entry point
int main(int argc, char *argv[]) {
    printf("You should see this message (QWERTY)\n");
    std::cout << "Press any key to exit" << std::endl;
    std::cin.get();
    return EXIT_SUCCESS;
}
