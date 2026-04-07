#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("GameScene"),
    wantToChange(true),
    is_init(false)
{
}

Menu::~Menu()
{

}

void Menu::draw(Render& window)
{
    if (is_init == false)
    {
        rectangle.position = glm::vec3(675,325,0);
        rectangle.rotation = glm::vec3(0,0,0);
        rectangle.scale = glm::vec3(250,250,1);
        window.AddMesh("2D","assets/models/rectangle.obj");
        window.Add2DObject("2D",rectangle);
        is_init = true;
    }

}

void Menu::event()
{
    
}

void Menu::update(float dt)
{

}

bool Menu::wantToChangeScene()
{
    return wantToChange;
}

std::string Menu::getSceneChangeType()
{
    return scneneToChange;
}