#ifndef RENDER
#define RENDER

#include <iostream>
#include "Utiles.hpp"

class Render
{
public:

    Render() = default;
    virtual ~Render() = default;

    virtual void InitWindow() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Clear() = 0;
    virtual bool IsOpen() = 0;
    virtual void Events() = 0;
    virtual void AddMesh(std::string name, std::string path) = 0;
    virtual void AddObject(std::string mesh_name, Transform& transform) = 0;
    virtual void Add2DObject(std::string mesh_name, Transform& transform) = 0;
    virtual void ClearMesh() = 0;
    virtual void ClearObject() = 0;
    virtual void Clear2DObject() = 0;
    virtual void SetView(glm::vec3 position, glm::vec3 vecDirection) = 0;
    virtual glm::vec2 getMousePos() = 0;
    virtual bool IsMousePressed(int button) = 0;
};

#endif