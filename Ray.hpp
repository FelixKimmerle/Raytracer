#pragma once
#include "LinearAlgebra/StaticVector.hpp"

typedef StaticVector<float, 3> vec3;

class Ray
{
private:
    vec3 m_Origin;
    vec3 m_Direction;

public:
    Ray(const vec3 &p_Origin, const vec3 &p_Direction);
    ~Ray();
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(float t) const;
};
