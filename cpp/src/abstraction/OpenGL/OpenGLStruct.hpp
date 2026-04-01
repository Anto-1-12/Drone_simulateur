#ifndef OPENGLSTRUCT
#define OPENGLSTRUCT

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

struct Mesh {
    GLuint VAO;
    GLuint VBO;
    int vertexCount;
    std::string name;
};

struct Object {
    Mesh* mesh;
    glm::mat4 transform;
};

#endif