#ifndef RENDERTYPE
#define RENDERTYPE

#include <iostream>
#include "render.hpp"

//class abstraite
class RenderType{

    public:
        RenderType();
        ~RenderType();

        Render* getRenderFromType(std::string type, int width, int height);

};

#endif