#include <SFML/Graphics.hpp>
#include <iostream>
#include "Raytracer.hpp"
int main()
{

    Raytracer rc(sf::Vector2<unsigned int>(1000, 500));

    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    window.setVerticalSyncEnabled(true);

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

        window.draw(rc);
        rc.Update();
        window.display();
        sf::sleep(sf::seconds(1));
    }

    return 0;
}