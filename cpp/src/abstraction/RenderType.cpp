#include "RenderType.hpp"
#include "OpenGl_Render.hpp"

RenderType::RenderType()
{

}

RenderType::~RenderType()
{

}

Render* RenderType::getRenderFromType(std::string type, int width, int height)
{

    //on defini les types de render
    if (type == "OpenGL"){
        return new OpenGLRenderer(width,height);
    }

    //n'est pas sensé arriver
    return new OpenGLRenderer(width,height);
}