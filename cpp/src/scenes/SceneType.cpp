#include "SceneType.hpp"
#include "Menu.hpp"
#include "GameScene.hpp"

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
    else if (type == "GameScene"){
        return new GameScene();
    }

    //n'est pas sensé arriver
    return new Menu();
}