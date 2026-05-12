#ifndef GAMESCENE
#define GAMESCENE

#include "Scene.hpp"
#include "Utiles.hpp"

#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <chrono>

#include <nlohmann/json.hpp>


class GameScene : public Scene
{
    private:
        std::string scneneToChange;
        bool wantToChange;
        bool is_init;

        SOCKET sock;
        sockaddr_in server;
        using json = nlohmann::json;

        Transform cube;
        Transform drone;

        std::string buffer_accum;

    public:
        GameScene();
        ~GameScene();
        void event() override;
        void update(float dt,Render& window) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
        void sync();
        void sendMessage(std::string command);
};

#endif