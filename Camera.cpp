#include "Camera.hpp"

Camera::Camera(/* args */) : m_Origin({0, 0, 0}), m_Horizontal({4.0, 0, 0}), m_Vertical({0, 2, 0}), m_Lower_left_corner({-2.0, -1.0, -1.0})
{
}

Camera::~Camera()
{
}

Ray Camera::get_ray(float u, float v)
{
    return Ray(m_Origin,m_Lower_left_corner + m_Horizontal*u + m_Vertical*v - m_Origin);
}