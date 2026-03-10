#include "SceneManager.hpp"

//le scene manageur sert a gerer les scenes et a changer de scene active

//constructeur
SceneManager::SceneManager(Scene* scene_init,SceneType* scene_type_init)
{
    scene = scene_init;
    sceneType = scene_type_init;
};

//destructeur de SceneManager pour eviter les fuites
SceneManager::~SceneManager()
{
    delete scene;
    delete sceneType;
}


//methode pour changer de scene
void SceneManager::changeScene(Scene* newScene)
{
    
    //eviter le crash si on change sur la meme scene
    if (scene != newScene){
        // supression du contenu du pointeur scene
        delete scene;
    }

    // remplacement de scene par newScene
    scene = newScene;
}

//dessin de la scene
void SceneManager::draw(sf::RenderWindow& window)
{
    scene->draw(window);
}

//event de la scene
void SceneManager::event(const sf::Event& event)
{
    scene->event(event);
}

//update de la scene + detection de changement de scene
void SceneManager::update( float dt)
{
    scene->update(dt);
    
    //regarder si on veut changer de scene
    if(scene->wantToChangeScene())
    {
        //savoir la scene sur laquelle on veut changer
        std::string changeType = scene->getSceneChangeType();
        
        //transformer le changeType en Scene
        Scene* new_scene = sceneType->getSceneFromType(changeType);

        changeScene(new_scene);
    }
}