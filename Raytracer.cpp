#include "Raytracer.hpp"
#include "Sphere.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include <iostream>

vec3 color(const Ray &r, Object *world, unsigned int depth)
{
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        Ray scattered(vec3({0, 0, 0}), vec3({0, 0, 0}));
        vec3 attenuation;
        if (depth < 500 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3({0, 0, 0});
        }
    }

    vec3 unit_direction = r.direction().normalized();
    float t = 0.5 * (unit_direction[1] + 1.0);
    return vec3({1.0, 1.0, 1.0}) * (1.0 - t) + vec3({0.5, 0.7, 1.0}) * t;
}

Raytracer::Raytracer(sf::Vector2<unsigned int> p_Size) : m_Size(p_Size)
{
    m_Pixels = new sf::Uint8[p_Size.x * p_Size.y * 4];
    m_Last = new vec3[p_Size.x * p_Size.y];
    m_uiSample = 0;

    world.Add(new Sphere(vec3({0, 0, -1}), 0.5, new Lambertian(vec3({0.3, 0.1, 0.1}))));
    world.Add(new Sphere(vec3({0, -100.5, -1}), 100, new Lambertian(vec3({0.8, 0.8, 0.0}))));
    world.Add(new Sphere(vec3({1, 0, -1}), 0.5, new Metal(vec3({0.8, 0.6, 0.2}))));
    world.Add(new Sphere(vec3({-1, 0, -1}), 0.5, new Metal(vec3({0.8, 0.8, 0.8}))));


    number = std::thread::hardware_concurrency();
    isRun = true;
    fThreads = 0;
    for (unsigned int y = 0; y < number; y++)
    {
        m_Threads.push_back(std::thread(&Raytracer::Worker, this, y));
    }

    auto mmm = std::unique_lock<std::mutex>(m_mNotifyMutex);
    m_cvDoNotify.wait(mmm);
}
sf::Clock sfclock;

void Raytracer::Worker(unsigned int id)
{
    std::mutex m_mWorkMutex;
    mutex.lock();
    fThreads++;
    if (fThreads >= number)
    {
        m_cvDoNotify.notify_all();
    }
    mutex.unlock();
    while (isRun)
    {
        auto mmm = std::unique_lock<std::mutex>(m_mWorkMutex);
        m_cvDoWork.wait(mmm);
        if (!isRun)
        {
            break;
        }

        for (int j = id; j < m_Size.y * m_Size.x; j += number)
        {
            float u = float(j % m_Size.x + random_double()) / float(m_Size.x);
            float v = float(j / m_Size.x + random_double()) / float(m_Size.y);
            Ray r = cam.get_ray(u, v);
            vec3 col = color(r, &world, 0);
            if (m_uiSample != 0)
            {
                m_Last[j] = (m_Last[j] * m_uiSample + col) / float(m_uiSample + 1);
            }
            else
            {
                m_Last[j] = col;
            }
            int index = (j)*4;

            m_Pixels[index] = sqrt(m_Last[j][0]) * 255.99;
            m_Pixels[index + 1] = sqrt(m_Last[j][1]) * 255.99;
            m_Pixels[index + 2] = sqrt(m_Last[j][2]) * 255.99;
            m_Pixels[index + 3] = 255;
        }

        mutex.lock();
        fThreads++;
        if (fThreads >= number)
        {
            m_cvDoNotify.notify_all();
        }
        mutex.unlock();
    }
}

Raytracer::~Raytracer()
{
    isRun = false;
    m_cvDoWork.notify_all();
    for (auto x = m_Threads.begin(); x != m_Threads.end(); x++)
    {
        x->join();
    }
    
    m_Threads.clear();
}
void Raytracer::Update()
{
    sf::Clock xclock;
    fThreads = 0;
    sfclock.restart();

    m_cvDoWork.notify_all();
    auto mmm = std::unique_lock<std::mutex>(m_mNotifyMutex);
    m_cvDoNotify.wait(mmm);

    m_Image.create(m_Size.x, m_Size.y, m_Pixels);
    m_Image.flipVertically();
    m_Texture.loadFromImage(m_Image);
    m_Sprite.setTexture(m_Texture, true);

    m_uiSample++;
    std::cout << m_uiSample << std::endl;
}

void Raytracer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_Sprite, states);
}