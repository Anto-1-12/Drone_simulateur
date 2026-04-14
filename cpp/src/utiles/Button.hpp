#ifndef BUTTON
#define BUTTON
#include <iostream>
#include <glm/glm.hpp>
#include "render.hpp"
#include "Utiles.hpp"

class Button
{
private:
    Transform buttonPos;

    bool isInit;

    bool mouseIsOnItSelf = false;
    bool isClicked = false;

    std::string texturePath;
    std::string name;

    bool checkMouse(Render& window);

public:
    Button(glm::vec2 pos, glm::vec2 size, std::string txtPath, std::string meshName);
    ~Button();
    void draw(Render& window);
    void update(Render& window);
    void setCoo(float x,float y);

    void resize(glm::vec2 size);
    glm::vec2 get_size();

    bool buttonIsClicked();
};

#endif