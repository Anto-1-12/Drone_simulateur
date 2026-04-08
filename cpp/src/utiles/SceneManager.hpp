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
        void event();
        void update(float dt,Render& window);
        void draw(Render& window);
};

#endif