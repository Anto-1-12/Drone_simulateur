#include "Button.hpp"

Button::Button(glm::vec2 pos, glm::vec2 size, std::string txtPath, std::string meshName):
    isInit(false),
    texturePath(txtPath),
    name(meshName)
{
    buttonPos.position = glm::vec3(pos,0);
    buttonPos.rotation = glm::vec3(0,0,0);
    buttonPos.scale = glm::vec3(size,1);
}

Button::~Button()
{

}

// verifie si la sourie est sur le boutton
bool Button::checkMouse(Render& window)
{
    glm::vec2 mPos = window.getMousePos();

    if (mPos.x > buttonPos.position.x && mPos.x < buttonPos.position.x + buttonPos.scale.x  &&  mPos.y > buttonPos.position.y && mPos.y < buttonPos.position.y + buttonPos.scale.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Button::draw(Render& window)
{
    if (!isInit)
    {
        window.AddMesh(name,"assets/models/rectangle.obj",texturePath);
        window.Add2DObject(name,buttonPos);
        isInit = true;
    }
}

void Button::update(Render& window)
{
    if (this->checkMouse(window))
    {
        mouseIsOnItSelf = true;
    }
    else
    {
        mouseIsOnItSelf = false;
    }
    if (window.IsMousePressed(0) && mouseIsOnItSelf)
    {
        isClicked = true;
    }
    else
    {
        isClicked = false;
    }
}

void Button::setCoo(float x, float y)
{
    buttonPos.position.x = x ;
    buttonPos.position.y = y ;
}

bool Button::buttonIsClicked()
{
    return isClicked;
}

void Button::resize(glm::vec2 size)
{
    buttonPos.scale = glm::vec3(size,1);
}

glm::vec2 Button::get_size()
{
    return glm::vec2(buttonPos.scale.x,buttonPos.scale.y);
}