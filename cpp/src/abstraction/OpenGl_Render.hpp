#ifndef OPENGLRENDERER
#define OPENGLRENDERER

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.hpp"

class OpenGLRenderer : public Render
{
    private:
         GLFWwindow* window;
         glm::ivec2 size_screen;

    public:
         OpenGLRenderer(int width, int hieght);
         ~OpenGLRenderer();
         void Init() override;
         void Update() override;
         void Clear() override;
         bool IsOpen() override;
         void Events() override;
};

#endif