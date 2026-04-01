#ifndef OPENGLSTRUCT
#define OPENGLSTRUCT

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Mesh {
    GLuint VAO;
    GLuint VBO;
    int vertexCount;
};

struct Object {
    Mesh* mesh;
    glm::mat4 transform;
};

#endif