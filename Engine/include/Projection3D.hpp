#ifndef PROJECTION3D
#define PROJECTION3D
#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f projection(sf::Vector3f point_coo, sf::Vector2f size_screen, float fov);
sf::Vector3f turn_point(sf::Vector3f camera_coo, sf::Vector3f point_coo,sf::Vector3f camera_rotation);
sf::Vector3f rotate_model(sf::Vector3f point_coo,sf::Vector3f rotation);

#endif