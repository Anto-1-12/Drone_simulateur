#ifndef MENU
#define MENU

#include "Scene.hpp"
#include "Button.hpp"

class Menu : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;
        bool is_init;
        Transform rectangle;

        Button button1;
        Button button2;

    public:
        Menu();
        ~Menu();
        void event() override;
        void update(float dt,Render& window) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};

#endif