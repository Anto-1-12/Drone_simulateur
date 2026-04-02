#ifndef UTILES
#define UTILES

#include <fstream>
#include <sstream>
#include <string>
#include <TOL/tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <iostream>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

bool loadObjWithTiny(const std::string& filename, std::vector<Vertex>& outVertices);

std::string readFile(const char* path);

#endif