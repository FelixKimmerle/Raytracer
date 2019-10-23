#include "Ray.hpp"

Ray::Ray(const vec3 &p_Origin, const vec3 &p_Direction) : m_Origin(p_Origin), m_Direction(p_Direction)
{
}

Ray::~Ray()
{
}

vec3 Ray::origin() const
{
    return m_Origin;
}
vec3 Ray::direction() const
{
    return m_Direction;
}
vec3 Ray::point_at_parameter(float t) const
{
    return m_Origin + m_Direction * t;
}