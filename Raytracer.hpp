#pragma once
#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include "Camera.hpp"
#include "Container.hpp"
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

class Raytracer : public sf::Drawable, public sf::Transformable
{
private:
    sf::Uint8 *m_Pixels;
    vec3 *m_Last;

    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    sf::Image m_Image;

    unsigned int m_uiSample;

    Container world;
    Camera cam;

    sf::Vector2<unsigned int> m_Size;

    std::vector<std::thread> m_Threads;
    unsigned int number;
    bool isRun;
    std::atomic<unsigned int> fThreads;
    void Worker(unsigned int id);

    std::condition_variable m_cvDoWork;

    std::condition_variable m_cvDoNotify;
    std::mutex m_mNotifyMutex;

    std::mutex mutex;


public:
    Raytracer(sf::Vector2<unsigned int> p_Size);
    ~Raytracer();
    void Update();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
