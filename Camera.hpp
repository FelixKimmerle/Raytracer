#pragma once
#include "Ray.hpp"
class Camera
{
private:
    vec3 m_Origin, m_Horizontal, m_Vertical, m_Lower_left_corner; 
public:
    Camera(/* args */);
    ~Camera();
    Ray get_ray(float u, float v);
};
