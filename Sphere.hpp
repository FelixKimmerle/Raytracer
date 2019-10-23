#pragma once

#include "Hittable.hpp"

class Sphere: public Hittable  {
    public:
        Sphere() {}
        Sphere(vec3 cen, float r) : center(cen), radius(r)  {};
        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = oc.dot(r.direction());
    float c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}