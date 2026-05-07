#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.hpp"

int main() {
    Game game = Game();
    game.run();
}