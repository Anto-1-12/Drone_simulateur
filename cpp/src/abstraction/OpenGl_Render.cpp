#include "OpenGl_Render.hpp"

OpenGLRenderer::OpenGLRenderer(int width,int height): 
    Render(),
    size_screen(glm::ivec2(width,height))
{
    Init();
}

OpenGLRenderer::~OpenGLRenderer()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLRenderer::Init()
{
    glfwInit();
    window = glfwCreateWindow(size_screen.x, size_screen.y, "OpenGL", NULL, NULL);
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

bool OpenGLRenderer::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void OpenGLRenderer::Events()
{
    glfwPollEvents();
}