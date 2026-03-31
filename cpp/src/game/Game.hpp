#ifndef GAME
#define GAME

#include <chrono>
#include "SceneManager.hpp"
#include "SceneType.hpp"
#include "Menu.hpp"
#include "render.hpp"
#include "RenderType.hpp"

class Game
{
private:
    //variables
    Render* renderer;

    bool isFullScreen = false;

    // le scene manager
    SceneManager sceneManager;

    float dt;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;

public:
    //methode lancement de la boucle
    void run();

    //constructeur
    Game();

    // destructeur ~Game();
};

#endif