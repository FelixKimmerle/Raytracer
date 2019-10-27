#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Container.hpp"
#include "Sphere.hpp"
#include "Random.hpp"
#include <iostream>
#include "Metal.hpp"
#include "Lambertian.hpp"
int max = 5;
unsigned int num = 0;

vec3 color(const Ray &r, Object *world, unsigned int depth)
{
    num++;
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

int main()
{

    unsigned int nx = 200 * 8;
    unsigned int ny = 100 * 8;
    unsigned int ns = 100;

    size_t size = nx * ny * 4;
    sf::Uint8 *pixels = new sf::Uint8[size];
    vec3 *vecs = new vec3[nx * ny];

    vec3 lower_left_corner({-2.0, -1.0, -1.0});
    vec3 horizontal({4.0, 0.0, 0.0});
    vec3 vertical({0.0, 2.0, 0.0});
    vec3 origin({0.0, 0.0, 0.0});

    Container world;
    world.Add(new Sphere(vec3({0, 0, -1}), 0.5, new Lambertian(vec3({0.3, 0.1, 0.1}))));
    world.Add(new Sphere(vec3({0, -100.5, -1}), 100, new Lambertian(vec3({0.8, 0.8, 0.0}))));
    world.Add(new Sphere(vec3({1, 0, -1}), 0.5, new Metal(vec3({0.8, 0.6, 0.2}))));
    world.Add(new Sphere(vec3({-1, 0, -1}), 0.5, new Metal(vec3({0.8, 0.8, 0.8}))));
    Camera cam;

    std::cout << num << std::endl;

    sf::RenderWindow window(sf::VideoMode(nx, ny), "SFML works!");
    window.setVerticalSyncEnabled(true);

    sf::Image image;

    sf::Texture texture;

    sf::Sprite sprite(texture);

    unsigned int samples = 0;

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

        int index = 0;
        int pixel = 0;
        for (int j = ny - 1; j >= 0; j--)
        {
            for (int i = 0; i < nx; i++)
            {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                Ray r = cam.get_ray(u, v);
                vec3 col = color(r, &world, 0);
                if (samples != 0)
                {
                    vecs[pixel] = (vecs[pixel] * samples + col) / float(samples + 1);
                }
                else
                {
                    vecs[pixel] = col;
                }

                pixels[index] = sqrt(vecs[pixel][0]) * 255.99;
                pixels[index + 1] = sqrt(vecs[pixel][1]) * 255.99;
                pixels[index + 2] = sqrt(vecs[pixel][2]) * 255.99;
                pixels[index + 3] = 255;
                index += 4;
                pixel++;
            }
        }
        std::cout << samples << std::endl;
        samples++;
        image.create(nx, ny, pixels);
        texture.loadFromImage(image);
        sprite.setTexture(texture, true);

        window.draw(sprite);
        window.display();
    }
    delete[] pixels;

    return 0;
}