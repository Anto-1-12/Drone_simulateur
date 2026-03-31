#include "OpenGl_Render.hpp"

OpenGLRenderer::OpenGLRenderer()
{
window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
}

void OpenGLRenderer::Init()
{
    glfwInit();
    glfwMakeContextCurrent(window);
     gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}