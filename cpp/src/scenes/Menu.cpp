#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false)
{
}

Menu::~Menu()
{

}

void Menu::draw(Render& window)
{
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