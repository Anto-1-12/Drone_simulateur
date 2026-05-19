#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("GameScene"),
    wantToChange(false),
    is_init(false),
    button1(glm::vec2(675,125),glm::vec2(250,250),"assets/textures/Play_button.png","B1"),
    button2(glm::vec2(675,475),glm::vec2(250,250),"assets/textures/Play_button.png","B2")
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
    button2.update(window);

    if(button1.buttonIsClicked())
    {
        scneneToChange = "GameScene";
        wantToChange = true;
    }
    if(button2.buttonIsClicked())
    {
        scneneToChange = "GameSceneAuto";
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