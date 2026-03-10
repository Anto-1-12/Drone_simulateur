#ifndef SCENETYPE
#define SCENETYPE

#include "Scene.hpp"

//class abstraite
//objectif, etre un outils pour créer des scenes, chaque projet en aura un defini
class SceneType{

    public:
        SceneType();
        ~SceneType();

        Scene* getSceneFromType(std::string type);

};

#endif