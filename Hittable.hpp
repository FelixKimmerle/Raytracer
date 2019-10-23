#pragma once
#include "Ray.hpp"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class Hittable  {
    public:
        virtual bool hit(
            const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};