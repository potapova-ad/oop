#include <iostream>
#include "slider.hpp"
#include "circle.hpp"

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Slider", sf::Style::Default, settings);
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile("../consolas.ttf")) {
        std::cout << "Can't load button font" << std::endl;
    }

    Slider radius_slider {window, font, sf::Vector2f({100., 100.}), {0, 100}, {255, 255, 255}} ;
    Slider red_slider {window, font, sf::Vector2f({100., 200.}), {0, 255}, {255, 0, 0}} ;
    Slider green_slider {window, font, sf::Vector2f({100., 300.}), {0, 255}, {0, 255, 0}} ;
    Slider blue_slider {window, font, sf::Vector2f({100., 400.}), {0, 255}, {0, 0, 255}} ;

    Circle Circle = {{600, 300}, 10};

    while (window.isOpen()) {


        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
                break;

            }

            radius_slider.catchEvent(event);
            red_slider.catchEvent(event);
            green_slider.catchEvent(event);
            blue_slider.catchEvent(event);
            Circle.radius = radius_slider.getCurrentValue();
            Circle.color = { (sf::Uint8)red_slider.getCurrentValue(), (sf::Uint8)green_slider.getCurrentValue(), (sf::Uint8)blue_slider.getCurrentValue() } ;
            window.clear(sf::Color::Black);
            radius_slider.draw();
            red_slider.draw();
            green_slider.draw();
            blue_slider.draw();
            Circle.draw(window);
            window.display();
        }
    }

    return 0;
}