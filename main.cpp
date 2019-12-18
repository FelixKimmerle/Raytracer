#include <SFML/Graphics.hpp>
#include <iostream>
#include "Raytracer.hpp"
sf::Clock sfclock2;
#include <iostream>
int main()
{

    Raytracer rc(sf::Vector2<unsigned int>(1000, 500));

    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");
    window.setVerticalSyncEnabled(true);
    sfclock2.restart();
    unsigned int counter = 0;
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
        if(sfclock2.getElapsedTime().asMilliseconds() > 1000)
        {
            std::cout << counter << std::endl;
            counter = 0;
            sfclock2.restart();
        }
        window.draw(rc);
        rc.Update();
        window.display();
        counter++;
    }

    return 0;
}