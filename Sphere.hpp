#pragma once

#include "Object.hpp"

class Sphere : public Object
{
public:
    Sphere() {}
    Sphere(vec3 cen, float r,Material *p_mat) : center(cen), radius(r), mat_ptr(p_mat){};
    virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const;
    vec3 center;
    float radius;
    Material *mat_ptr;
};

