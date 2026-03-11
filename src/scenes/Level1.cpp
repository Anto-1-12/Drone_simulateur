#include "Level1.hpp"

Level1::Level1(): 
    Scene(),
    menu_button("assets/textures/Button.png","assets/textures/Button2.png","assets/fonts/Runtti-Regular.ttf","Menu",sf::Color(255,255,255),sf::Color(200,200,200),170,70,70,2.0f),
    scneneToChange("Menu"),
    wantToChange(false),
    
    //coo du drone
    coo(0,-100,0),
    rotation(0,0,0),
    vitesse(60),
    relativeCooCam(0,-20,-10)
    
    //test
{
    //le model du drone sera tjr le premier model
    map_obj.push_back(Model3D(coo,"assets/models/drone.obj",1));
    map_obj.push_back(Model3D(sf::Vector3f(0,0,0),"assets/models/block_a_la_main.obj",10));

}

Level1::~Level1()
{
    
}

void Level1::draw(sf::RenderWindow& window)
{

    sf::Vector3f Vec = rotate_model(relativeCooCam,sf::Vector3f(rotation.x,0,0));
    sf::Vector3f CamPos = coo - Vec;

    float yawn = atan2(Vec.x,Vec.y);

    sf::Vector3f CamRotation = sf::Vector3f(yawn,rotation.y,rotation.z);

    for (int i = 0; i < map_obj.size() ; i++)
    {
        std::vector<sf::Vector3f> vertexs = map_obj[i].getVertexs();

        std::vector<sf::Vector2f> points;

        for (int a = 0; a < vertexs.size() ; a++)
        {
            sf::Vector3f xyz = turn_point(CamPos,vertexs[a],CamRotation);

            //verifier si l'objet est devan ou deriere pour ne pas le projetter dans le cas contraire
            if(xyz.y > 0)
            {
                points.push_back(projection(xyz,window.getView().getSize(),M_PI/2));
            }
            else
            {
                //pour identifier les points non projeter et garder l'ordre dans la liste de point
                points.push_back(sf::Vector2f(-10000, -10000));
            }
        }

        std::vector<std::vector<int>> faces = map_obj[i].getFaces();
        std::vector<sf::Vector3f> vns = map_obj[i].getVectorNormal();

        for ( int b = 0; b < faces.size(); b++)
        {
            sf::Vector3f vn = vns[b];
            sf::Vector3f vd = vn - CamPos;

            float dot_prod = vn.x*vd.x + vn.y*vd.y + vn.z*vd.z;

            if(dot_prod <= 0)
            {
                sf::ConvexShape triangle;
                triangle.setPointCount(faces[b].size());

                if (dot_prod < -255*2)
                {
                    dot_prod = -255 * 2;
                }
                else if (dot_prod > 0)
                {
                    dot_prod = 0;
                }

                //std::cout<<dot_prod<<std::endl;

                triangle.setFillColor(sf::Color(dot_prod * 0.5,dot_prod * 0.5,dot_prod * 0.5));

                sf::VertexArray lines(sf::PrimitiveType::LineStrip,faces[b].size());
            

                bool draw = true;

                for ( int  p = 0; p < faces[b].size(); p++)
                {
                    if (points[faces[b][p]] == sf::Vector2f(-10000, -10000))
                    {
                        draw = false;
                    }
                    lines[p].position = points[faces[b][p]];
                    lines[p].color = sf::Color::Red;
                    triangle.setPoint(p, points[faces[b][p]]);
                }

                if(draw)
                {
                    window.draw(triangle);
                    //window.draw(lines);
                }
            }
        }
    }

    menu_button.draw(window);
}

void Level1::event(const sf::Event& event)
{
    menu_button.event(event);
}

void Level1::update(float dt)
{

    sf::Vector3f Vec = rotate_model(relativeCooCam,sf::Vector3f(rotation.x,0,0));

    float yawn = atan2(Vec.x,Vec.y);

    sf::Vector3f CamRotation = sf::Vector3f(yawn,rotation.y,rotation.z);

    float forwardX = std::sin(CamRotation.x);
    float forwardY = std::cos(CamRotation.x);

    float rightX = std::cos(CamRotation.x);
    float rightY = -std::sin(CamRotation.x);

    if(menu_button.buttonIsClicked())
    {
        scneneToChange = "Menu";
        wantToChange = true;
    }

    // AVANCER
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        coo.x += forwardX * vitesse * dt;
        coo.y += forwardY * vitesse * dt;
    }

    // RECULER
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        coo.x -= forwardX * vitesse * dt;
        coo.y -= forwardY * vitesse * dt;
    }

    // GAUCHE (strafe)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        coo.x -= rightX * vitesse * dt;
        coo.y -= rightY * vitesse * dt;
    }

    // DROITE (strafe)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        coo.x += rightX * vitesse * dt;
        coo.y += rightY * vitesse * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        coo.z += vitesse * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        coo.z -= vitesse * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        rotation.x += (vitesse*2)/40 * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        rotation.x -= (vitesse*2)/40 * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        rotation.y -= (vitesse*2)/40 * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        rotation.y += (vitesse*2)/40 * dt;
    }

    map_obj[0].turn_model(sf::Vector3f(rotation.x,0,0),coo);

}

bool Level1::wantToChangeScene()
{
    return wantToChange;
}

std::string Level1::getSceneChangeType()
{
    return scneneToChange;
}