#pragma once

#include "Material.hpp"
#include "Random.hpp"

class Lambertian : public Material
{
public:
    Lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const Ray &r_in, const hit_record &rec,
                         vec3 &attenuation, Ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};
