#ifndef GAMESCENE
#define GAMESCENE

#include "Scene.hpp"
#include "Utiles.hpp"
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>

class GameScene : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;
        bool is_init;
        Transform cube;
        SOCKET sock;
        sockaddr_in server;

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