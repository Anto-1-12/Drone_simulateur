#include "Projection3D.hpp"

sf::Vector2f projection(sf::Vector3f point_coo, sf::Vector2f size_screen,float fov)
{

    float distance_plan_cam = (size_screen.x/2)/tan(fov/2);

    float x = (point_coo.x/point_coo.y) * distance_plan_cam + size_screen.x/2;
    float y = (-point_coo.z/point_coo.y) * distance_plan_cam + size_screen.y/2;

    return sf::Vector2f(x,y);
}

sf::Vector3f turn_point(sf::Vector3f camera_coo, sf::Vector3f point_coo,sf::Vector3f camera_rotation)
{
    float odx = point_coo.x - camera_coo.x;
    float ody = point_coo.y - camera_coo.y;
    float odz = point_coo.z - camera_coo.z;

    // ----- YAW -----
    float dx1 = odx * std::cos(camera_rotation.x) - ody * std::sin(camera_rotation.x);
    float dy1 = odx * std::sin(camera_rotation.x) + ody * std::cos(camera_rotation.x);
    float dz1 = odz;

    // ----- PITCH -----
    float dy2 = dy1 * std::cos(camera_rotation.y) - dz1 * std::sin(camera_rotation.y);
    float dz2 = dy1 * std::sin(camera_rotation.y) + dz1 * std::cos(camera_rotation.y);
    float dx2 = dx1;

    // ----- ROLL -----
    float dz3 = dz2 * std::cos(camera_rotation.z) - dx2 * std::sin(camera_rotation.z);
    float dx3 = dz2 * std::sin(camera_rotation.z) + dx2 * std::cos(camera_rotation.z);
    float dy3 = dy2;

    return sf::Vector3f(dx3,dy3,dz3);
}

sf::Vector3f rotate_model(sf::Vector3f point_coo,sf::Vector3f rotation)
{

    // ----- YAW -----
    float dx1 = point_coo.x * std::cos(rotation.x) - point_coo.y * std::sin(rotation.x);
    float dy1 = point_coo.x * std::sin(rotation.x) + point_coo.y * std::cos(rotation.x);
    float dz1 = point_coo.z;

    // ----- PITCH -----
    float dy2 = dy1 * std::cos(rotation.y) - dz1 * std::sin(rotation.y);
    float dz2 = dy1 * std::sin(rotation.y) + dz1 * std::cos(rotation.y);
    float dx2 = dx1;

    // ----- ROLL -----
    float dz3 = dz2 * std::cos(rotation.z) - dx2 * std::sin(rotation.z);
    float dx3 = dz2 * std::sin(rotation.z) + dx2 * std::cos(rotation.z);
    float dy3 = dy2;

    return sf::Vector3f(dx3,dy3,dz3);
}