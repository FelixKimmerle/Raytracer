#include <SFML/Graphics.hpp>
#include "vec3.hpp"

int main()
{

    unsigned int nx = 800;
    unsigned int ny = 600;

    sf::RenderWindow window(sf::VideoMode(nx, ny), "SFML works!");
    window.setVerticalSyncEnabled(true);
    size_t size = nx * ny * 4;
    sf::Uint8 *pixels = new sf::Uint8[size];

    int index = 0;
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;

            pixels[index] = r * 255.99;
            pixels[index + 1] = g * 255.99;
            pixels[index + 2] = b * 255.99;
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