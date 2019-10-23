#include <SFML/Graphics.hpp>
#include "Ray.hpp"

vec3 color(const Ray &r)
{
    vec3 unit_direction = r.direction().normalized();
    float t = 0.5 * (unit_direction[1] + 1.0);
    return vec3({1.0, 1.0, 1.0}) * (1.0 - t) + vec3({0.5, 0.7, 1.0}) * t;
}

int main()
{

    unsigned int nx = 800;
    unsigned int ny = 600;

    sf::RenderWindow window(sf::VideoMode(nx, ny), "SFML works!");
    window.setVerticalSyncEnabled(true);
    size_t size = nx * ny * 4;
    sf::Uint8 *pixels = new sf::Uint8[size];

    int index = 0;
    vec3 lower_left_corner({-2.0, -1.0, -1.0});
    vec3 horizontal({4.0, 0.0, 0.0});
    vec3 vertical({0.0, 2.0, 0.0});
    vec3 origin({0.0, 0.0, 0.0});
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lower_left_corner + horizontal * u + vertical * v);
            vec3 col = color(r);
            pixels[index] = col[0] * 255.99;
            pixels[index + 1] = col[1] * 255.99;
            pixels[index + 2] = col[2] * 255.99;
            pixels[index + 3] = 255;
            index += 4;
        }
    }

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