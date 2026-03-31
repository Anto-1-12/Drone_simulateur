#include "OpenGl_Render.hpp"

OpenGLRenderer::OpenGLRenderer()
{
Init();
window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
}

OpenGLRenderer::OpenGLRenderer()
{
glfwTerminate();
}

void OpenGLRenderer::Init()
{
    glfwInit();
    glfwMakeContextCurrent(window);
     gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::Update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}