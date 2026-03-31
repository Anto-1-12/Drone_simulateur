#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.hpp"

// Callback en cas de redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Gestion des entrées clavier (échap pour fermer)
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    Game game = Game();
    game.run();
}