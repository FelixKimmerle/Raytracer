#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Container.hpp"
#include "Sphere.hpp"
#include "Random.hpp"
#include <iostream>
int max = 5;
unsigned int curr = 0;

vec3 color(const Ray &r, Object *world)
{
    curr++;
    hit_record rec;
    if (world->hit(r, 0.0001, MAXFLOAT, rec))
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        vec3 ret = vec3({1, 1, 1});
        if (curr < 10)
        {
            vec3 ret = color(Ray(rec.p, target - rec.p), world) * 0.5;
            curr--;
            return ret;
        }
    }
    vec3 unit_direction = r.direction().normalized();
    float t = 0.5 * (unit_direction[1] + 1.0);
    vec3 ret = vec3({1.0, 1.0, 1.0}) * (1.0 - t) + vec3({0.5, 0.7, 1.0}) * t;
    curr--;
    return ret;
}

int main()
{

    unsigned int nx = 200 * 8;
    unsigned int ny = 100 * 8;
    unsigned int ns = 100;

    size_t size = nx * ny * 4;
    sf::Uint8 *pixels = new sf::Uint8[size];

    int index = 0;
    vec3 lower_left_corner({-2.0, -1.0, -1.0});
    vec3 horizontal({4.0, 0.0, 0.0});
    vec3 vertical({0.0, 2.0, 0.0});
    vec3 origin({0.0, 0.0, 0.0});

    Container world;
    world.Add(new Sphere(vec3({0, 0, -1}), 0.5));
    world.Add(new Sphere(vec3({0, -100.5, -1}), 100));
    Camera cam;

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col({0, 0, 0});
            for (unsigned int s = 0; s < ns; s++)
            {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                Ray r = cam.get_ray(u, v);
                col += color(r, &world);
            }
            col /= float(ns);

            pixels[index] = sqrt(col[0]) * 255.99;
            pixels[index + 1] = sqrt(col[1]) * 255.99;
            pixels[index + 2] = sqrt(col[2]) * 255.99;
            pixels[index + 3] = 255;
            index += 4;
        }
    }

    sf::RenderWindow window(sf::VideoMode(nx, ny), "SFML works!");
    window.setVerticalSyncEnabled(true);

    sf::Image image;
    image.create(nx, ny, pixels);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
    delete[] pixels;

    return 0;
}