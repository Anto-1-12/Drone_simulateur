#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    // Initialisation GLFW
    if (!glfwInit()) {
        std::cerr << "Erreur initialisation GLFW\n";
        return -1;
    }

    // Version OpenGL 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour MacOS
#endif

    // Création fenêtre
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur création fenêtre GLFW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialisation Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erreur initialisation Glad\n";
        return -1;
    }

    // Taille viewport initiale
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Boucle principale
    while (!glfwWindowShouldClose(window)) {
        // Entrées
        processInput(window);

        // Couleur de fond (bleu clair)
        glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Affichage
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Nettoyage
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}