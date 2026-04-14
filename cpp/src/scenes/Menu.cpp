#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("GameScene"),
    wantToChange(false),
    is_init(false),
    button1(glm::vec2(675,325),glm::vec2(250,250),"assets/textures/tkt.png","B1"),
    button2(glm::vec2(0,0),glm::vec2(250,250),"assets/textures/texture.png","B2")
{
}

Menu::~Menu()
{

}

void Menu::draw(Render& window)
{
    if (is_init == false)
    {
        window.ClearMesh();
        window.ClearObject();
        window.Clear2DObject();
        is_init = true;
    }
    
    button1.draw(window);
    button2.draw(window);

}

void Menu::event()
{
    
}

void Menu::update(float dt,Render& window)
{
    button1.update(window);

    if(button1.buttonIsClicked())
    {
        scneneToChange = "GameScene";
        wantToChange = true;
    }
}

bool Menu::wantToChangeScene()
{
    return wantToChange;
}

std::string Menu::getSceneChangeType()
{
    return scneneToChange;
}