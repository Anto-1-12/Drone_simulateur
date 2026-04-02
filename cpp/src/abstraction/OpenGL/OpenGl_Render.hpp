#ifndef OPENGLRENDERER
#define OPENGLRENDERER

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.hpp"
#include "OpenGLStruct.hpp"
#include "Utiles.hpp"

class OpenGLRenderer : public Render
{
     private:
          GLFWwindow* window;
          glm::ivec2 size_screen;
          std::vector<Mesh> all_mesh;
          std::vector<Object> all_object;
          GLuint modelLoc;
          GLuint vertexShader;
          GLuint fragmentShader;
          GLuint shaderProgram;

     public:
     
          OpenGLRenderer(int width, int hieght);
          ~OpenGLRenderer();

          void InitWindow() override;
          void Init() override;
          void Update() override;
          void Clear() override;
          bool IsOpen() override;
          void Events() override;
          void AddMesh() override;
          void AddObject() override;
};

#endif