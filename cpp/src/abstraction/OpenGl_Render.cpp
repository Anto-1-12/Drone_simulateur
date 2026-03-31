#include "OpenGl_Render.hpp"

void OpenGLRenderer::Init()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}