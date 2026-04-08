#include "Button.hpp"

Button::Button(glm::vec2 pos, glm::vec2 size):
    isInit(false)
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
        window.AddMesh("2D","assets/models/rectangle.obj");
        window.Add2DObject("2D",buttonPos);
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