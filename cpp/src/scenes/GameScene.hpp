#ifndef GAMESCENE
#define GAMESCENE

#include "Scene.hpp"

class GameScene : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;

    public:
        GameScene();
        ~GameScene();
        void event() override;
        void update(float dt) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};

#endif