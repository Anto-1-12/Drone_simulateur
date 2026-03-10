#ifndef SCENE
#define SCENE

#include <SFML/Graphics.hpp>

//class contenant les caracteristiquesde toutes les scenes 
//class abstraite
class Scene {

public:

    virtual ~Scene() = default;
    Scene() = default;
    
    //methode d'update du jeu
    virtual void event(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    //methode pour le changement de scene
    virtual bool wantToChangeScene() = 0;
    virtual std::string getSceneChangeType() = 0;
    
};

#endif