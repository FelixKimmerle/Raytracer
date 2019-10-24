#pragma once

#include <functional>
#include <random>
#include "Object.hpp"

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> rand_generator =
        std::bind(distribution, generator);
    return rand_generator();
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = vec3({random_double(), random_double(), random_double()})*2 - vec3({1,1,1});
    } while (std::pow(p.Length(),2) >= 1.0);
    return p;
}