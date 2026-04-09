#ifndef OPENGLSTRUCT
#define OPENGLSTRUCT

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Utiles.hpp"

struct Mesh {
    GLuint VAO;
    GLuint VBO;
    int vertexCount;
    std::string name;
    unsigned int texture;
};

struct Object {
    Mesh* mesh;
    Transform* transform;
};

#endif