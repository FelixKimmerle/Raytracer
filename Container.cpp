#include "Container.hpp"

Container::Container()
{
}
Container::~Container()
{
    for (auto &&i : m_Data)
    {
        delete i;
    }
    m_Data.clear();
}

void Container::Add(Object *data)
{
    m_Data.push_back(data);
}


bool Container::hit(const Ray &r, float t_min, float t_max,
                    hit_record &rec) const
{

    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (auto &&i : m_Data)
    {
        if (i->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    
    return hit_anything;
}