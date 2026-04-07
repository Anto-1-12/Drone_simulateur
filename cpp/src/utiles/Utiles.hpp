#ifndef UTILES
#define UTILES

#include <fstream>
#include <sstream>
#include <string>
#include <TOL/tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation; // euler angles
    glm::vec3 scale;
};

bool loadObjWithTiny(const std::string& filename, std::vector<Vertex>& outVertices);

std::string readFile(const char* path);

glm::mat4 computeModelMatrix(const Transform& t);

#endif