#ifndef GAMESCENEAUTO
#define GAMESCENEAUTO

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


class GameSceneAuto : public Scene
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
        Transform grond;

        std::string buffer_accum;

        float pitch;
        float yawn;

        bool is_R_pressed = false;
        bool is_F_pressed = false;
        bool is_H_pressed = false;

    public:
        GameSceneAuto();
        ~GameSceneAuto();
        void event() override;
        void update(float dt,Render& window) override;
        void draw(Render& window) override;

        bool wantToChangeScene() override;
        std::string getSceneChangeType() override;
        void sync(bool debug);
        void sendMessage(std::string command);
};

#endif