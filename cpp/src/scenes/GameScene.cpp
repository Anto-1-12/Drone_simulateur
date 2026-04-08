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

        window.ClearMesh();
        window.ClearObject();
        window.Clear2DObject();

        cube.position = glm::vec3(0,-3.3,0);
        cube.rotation = glm::vec3(0,0,0);
        cube.scale = glm::vec3(2.5,2.5,2.5);
        window.AddMesh("test","assets/models/tourEiffel.obj");
        window.AddObject("test",cube);
        is_init = true;
    }
}

void GameScene::event()
{
    
}

void GameScene::update(float dt,Render& window)
{
    cube.rotation.y += 20 * dt;
    //65 = Q
    //87 = Z
    if (window.IsKeyPressed(87))
    {
        std::cout<<"test"<<std::endl;
    }
}

bool GameScene::wantToChangeScene()
{
    return wantToChange;
}

std::string GameScene::getSceneChangeType()
{
    return scneneToChange;
}