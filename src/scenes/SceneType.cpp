#include "SceneType.hpp"
#include "Menu.hpp"
#include "Level1.hpp"

//constructeur
SceneType::SceneType()
{

}

//destructeur
SceneType::~SceneType()
{

}

Scene* SceneType::getSceneFromType(std::string type)
{
    //on defini les types de scenes
    if (type == "Menu"){
        return new Menu();
    }
    else if (type == "Level1"){
        return new Level1();
    }

    //n'est pas sensé arriver
    return new Menu();
}