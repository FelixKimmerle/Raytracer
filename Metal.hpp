#pragma once

#include "Material.hpp"

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - n * (2 * v.dot(n));
}

class Metal : public Material
{
public:
    Metal(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const Ray &r_in, const hit_record &rec,
                         vec3 &attenuation, Ray &scattered) const
    {
        vec3 reflected = reflect(r_in.direction().normalized(), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (scattered.direction().dot(rec.normal) > 0);
    }
    vec3 albedo;
};