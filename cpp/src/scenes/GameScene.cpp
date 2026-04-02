#include "GameScene.hpp"

GameScene::GameScene(): 
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false),
    is_init(false)
{
}

GameScene::~GameScene()
{

}

void GameScene::draw(Render& window)
{
    if (is_init == false)
    {
        window.AddMesh();
        window.AddObject();
        is_init = true;
    }
}

void GameScene::event()
{
    
}

void GameScene::update(float dt)
{

}

bool GameScene::wantToChangeScene()
{
    return wantToChange;
}

std::string GameScene::getSceneChangeType()
{
    return scneneToChange;
}