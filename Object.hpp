#pragma once
#include "Ray.hpp"

class Material;
struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
    Material *mat_ptr;
};

class Object
{
public:
    virtual ~Object(){};
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};