#include "Game.hpp"

//initialisation des variables
Game::Game(): 
    //fenetre
    renderer(RenderType().getRenderFromType("OpenGL",1600,900)),
    //initialiser le SceneManager
    sceneManager(new Menu(),new SceneType()),
    //le delta time pour les corrections de déplacement
    dt(1.0f / 60.0f),
    //initialiser le chrono
    lastTime(std::chrono::high_resolution_clock::now())
{
}

//La methode run
void Game::run()
{
    float accumulator = 0.0f;

    //tant que la fenetre est ouverte
    while (renderer->IsOpen())
    {
        
        //temps entre deux tour de boucle
        auto now = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;
        //on ajoute le temps écoulé a l'accumulateur
        accumulator += frameTime;

        //             update le SceneManager
        //---------------------------------------------
        while (accumulator >= dt) 
        {
            
            sceneManager.update(dt);
            // reinitialisation de l'accumulateur
            accumulator -= dt;
        }
        
        //               Zone de dessin
        //---------------------------------------------
        renderer->Clear();
        
        //dessin de la scene
        sceneManager.draw(*renderer);

        renderer->Update();
        //---------------------------------------------

        renderer->Events();
    }

    delete(renderer);
}