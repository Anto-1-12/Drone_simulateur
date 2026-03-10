#ifndef MODEL3D
#define MODEL3D
#include "Projection3D.hpp"

#include <SFML/Graphics.hpp>
#include<iostream>
#include <cmath>

#include <sstream>
#include <fstream>


class Model3D
{
    private:
        sf::Vector3f coo;
        std::string file;
        std::vector<sf::Vector3f> points;
        std::vector<std::vector<int>> faces;
        std::vector<sf::Vector3f> v;
        std::vector<sf::Vector3f> vn;
        std::vector<sf::Vector3f> vn_by_face;

        bool is_show = true;

        float size;

    public:
        Model3D(sf::Vector3f n_coo,std::string geo, float coeff_size);

        std::vector<sf::Vector3f> getVertexs();
        std::vector<std::vector<int>> getFaces();
        std::vector<sf::Vector3f> getVectorNormal();

        sf::Vector3f getCoo();

        void turn_model(sf::Vector3f rotation);

        bool get_show() {return is_show;};
        void set_show( bool is) {is_show = is;};

};

#endif