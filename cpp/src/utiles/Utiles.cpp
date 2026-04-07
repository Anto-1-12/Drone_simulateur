#include "Utiles.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "TOL/tiny_obj_loader.h"

//par chatgpt
std::string readFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

//par chatgpt
bool loadObjWithTiny(const std::string& filename, std::vector<Vertex>& outVertices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());
    if (!warn.empty()) std::cout << "WARN: " << warn << std::endl;
    if (!err.empty()) std::cout << "ERR: " << err << std::endl;
    if (!ret) return false;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};
            vertex.position = {
                attrib.vertices[3*index.vertex_index + 0],
                attrib.vertices[3*index.vertex_index + 1],
                attrib.vertices[3*index.vertex_index + 2]
            };

            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3*index.normal_index + 0],
                    attrib.normals[3*index.normal_index + 1],
                    attrib.normals[3*index.normal_index + 2]
                };
            }

            if (index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2*index.texcoord_index + 0],
                    attrib.texcoords[2*index.texcoord_index + 1]
                };
            }

            outVertices.push_back(vertex);
        }
    }

    return true;
}

//par chatgpt
glm::mat4 computeModelMatrix(const Transform& t) {
    glm::mat4 m = glm::translate(glm::mat4(1.0f), t.position);
    m = glm::rotate(m, glm::radians(t.rotation.x), glm::vec3(1,0,0));
    m = glm::rotate(m, glm::radians(t.rotation.y), glm::vec3(0,1,0));
    m = glm::rotate(m, glm::radians(t.rotation.z), glm::vec3(0,0,1));
    m = glm::scale(m, t.scale);
    return m;
}