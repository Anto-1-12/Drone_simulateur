#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("GameScene"),
    wantToChange(false),
    is_init(false),
    button1(glm::vec2(675,125),glm::vec2(250,250),"assets/textures/Play_button.png","assets/textures/Play_button_press.png","B1"),
    button2(glm::vec2(675,500),glm::vec2(250,250),"assets/textures/Play_button.png","assets/textures/Play_button_press.png","B2")
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

        manu_mode.position = glm::vec3(650,0,0);
        manu_mode.rotation = glm::vec3(0,0,0);
        manu_mode.scale = glm::vec3(300,75,1);

        window.AddMesh("manu mode","assets/models/rectangle.obj","assets/textures/mode_manu.png");
        window.Add2DObject("manu mode",manu_mode);

        auto_mode.position = glm::vec3(675,400,0);
        auto_mode.rotation = glm::vec3(0,0,0);
        auto_mode.scale = glm::vec3(250,75,1);

        window.AddMesh("auto mode","assets/models/rectangle.obj","assets/textures/mode_auto.png");
        window.Add2DObject("auto mode",auto_mode);

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