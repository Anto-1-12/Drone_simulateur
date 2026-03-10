#ifndef MENU
#define MENU

#include "Scene.hpp"
#include "Button.hpp"

class Menu : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;

        Button play_button;

        sf::Texture bg;
        sf::Sprite backGround;

    public:
        Menu();
        ~Menu();
        void event(const sf::Event& even) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};

#endif