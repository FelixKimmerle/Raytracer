#pragma once
#include "Object.hpp"
class Material
{
private:
    /* data */
public:
    virtual bool scatter(
        const Ray &r_in, const hit_record &rec, vec3 &attenuation,
        Ray &scattered) const = 0;
};
