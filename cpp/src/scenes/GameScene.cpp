#include "GameScene.hpp"

GameScene::GameScene(): 
    Scene(),
    scneneToChange("Menu"),
    wantToChange(false)
{
}

GameScene::~GameScene()
{

}

void GameScene::draw(Render& window)
{
    
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