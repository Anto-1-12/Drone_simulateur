#ifndef LEVEL1
#define LEVEL1
#include <cmath>
#include "Scene.hpp"
#include "Button.hpp"
#include "model3D.hpp"
#include "Projection3D.hpp"

class Level1 : public Scene
{
    private:

        std::string scneneToChange;
        bool wantToChange;

        Button menu_button;

        std::vector<Model3D> map_obj;
        sf::Vector3f coo;
        sf::Vector3f rotation;
        float vitesse;

    public:
        Level1();
        ~Level1();
        void event(const sf::Event& even) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};


#endif