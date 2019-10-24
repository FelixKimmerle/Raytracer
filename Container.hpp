#pragma once
#include "Object.hpp"
#include <vector>
class Container : public Object
{
private:
    std::vector<Object *> m_Data;

public:
    Container();
    ~Container();
    virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &rec) const;
    void Add(Object * data);
};
