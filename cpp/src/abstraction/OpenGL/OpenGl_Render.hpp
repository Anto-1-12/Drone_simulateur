#ifndef OPENGLRENDERER
#define OPENGLRENDERER

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.hpp"
#include "OpenGLStruct.hpp"

class OpenGLRenderer : public Render
{
     private:
          GLFWwindow* window;
          glm::ivec2 size_screen;
          std::vector<Mesh> all_mesh;
          std::vector<Object> all_object;
          std::vector<Object> all_2D_object;

          glm::mat4 view;
          glm::mat4 projection;
          glm::mat4 projection_2D;

          int modelLoc;
          int viewLoc;
          int projLoc;
          int nearLoc;
          int farLoc;
          
          GLuint vertexShader;
          GLuint fragmentShader;
          GLuint shaderProgram;

          GLuint vertexShader2D;
          GLuint fragmentShader2D;
          GLuint shaderProgram2D;

     public:
     
          OpenGLRenderer(int width, int hieght);
          ~OpenGLRenderer();

          void InitWindow() override;
          void Init() override;
          void Update() override;
          void Clear() override;
          bool IsOpen() override;
          void Events() override;
          void AddMesh(std::string name, std::string path) override;
          void AddObject(std::string mesh_name, Transform& transform) override;
          void Add2DObject(std::string mesh_name, Transform& transform) override;
          void SetView(glm::vec3 position, glm::vec3 vecDirection) override;
};

#endif