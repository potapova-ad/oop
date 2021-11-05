#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include "button.hpp"

sf::RenderWindow window(sf::VideoMode(300, 300), "Button");
sf::CircleShape circle(10);

void func() {
    srand(static_cast<char>(time(0)));
    circle.setFillColor(sf::Color({rand(), rand(), rand()}));
	window.clear(sf::Color::Black);
}


int main()
{
    circle.setPosition(sf::Vector2f{20, 20});
    circle.setFillColor(sf::Color({100, 0, 0}));

	Button button({100, 100}, {200, 200}, {0, 70, 0}, func);

	while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)  {
				window.close();
            }
			button.pressed(event, &window);
        }

        //window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

	return 0;
}