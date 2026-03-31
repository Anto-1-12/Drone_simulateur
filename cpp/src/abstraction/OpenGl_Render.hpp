#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.hpp"

class OpenGLRenderer : public Render
{
    private:
         GLFWwindow* window;
    public:
         OpenGLRenderer();
         ~OpenGLRenderer();
         void Init() override{};
         void Update() override{};
         void Clear() override{};
};