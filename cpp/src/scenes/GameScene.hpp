#ifndef GAMESCENE
#define GAMESCENE

#include "Scene.hpp"
#include "Utiles.hpp"

class GameScene : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;
        bool is_init;
        Transform cube;

    public:
        GameScene();
        ~GameScene();
        void event() override;
        void update(float dt,Render& window) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
};

#endif