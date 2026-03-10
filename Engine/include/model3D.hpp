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
        
        //current points
        std::vector<sf::Vector3f> points;
        
        //raw points
        std::vector<sf::Vector3f> v;

        //raw vector normal
        std::vector<sf::Vector3f> vn;
        
        //current vector normal 
        std::vector<sf::Vector3f> vn_by_face;

        //faces
        std::vector<std::vector<int>> faces;

        bool is_show = true;

        float size;

    public:
        Model3D(sf::Vector3f n_coo,std::string geo, float coeff_size);

        std::vector<sf::Vector3f> getVertexs();
        std::vector<std::vector<int>> getFaces();
        std::vector<sf::Vector3f> getVectorNormal();

        sf::Vector3f getCoo();

        void turn_model(sf::Vector3f rotation, sf::Vector3f coo);

        bool get_show() {return is_show;};
        void set_show( bool is) {is_show = is;};

        void tp(sf::Vector3f coo);

        void open_model();

};

#endif