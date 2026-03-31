#ifndef MENU
#define MENU

#include "Scene.hpp"

class Menu : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;

    public:
        Menu();
        ~Menu();
        void event() override;
        void update(float dt) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};

#endif