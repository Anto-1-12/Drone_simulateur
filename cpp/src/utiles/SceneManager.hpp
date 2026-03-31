#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "Scene.hpp"
#include "SceneType.hpp"
#include <iostream>

//def de la class SceneManager
class SceneManager{
    
    private:
        Scene* scene;
        SceneType* sceneType;
    
    public:

        SceneManager(Scene* scene, SceneType* scene_type_init);
        ~SceneManager();
        void changeScene(Scene* newScene);
        void event(const sf::Event& event);
        void update(float dt);
        void draw(sf::RenderWindow& window);
};

#endif