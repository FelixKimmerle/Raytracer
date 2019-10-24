#pragma once

#include "Object.hpp"

class Sphere : public Object
{
public:
    Sphere() {}
    Sphere(vec3 cen, float r) : center(cen), radius(r){};
    virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const;
    vec3 center;
    float radius;
};

