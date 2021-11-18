#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct Circle {

    Circle(sf::Vector2f position, float radius) : position(position), radius(radius) {}

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);
    }

    sf::Vector2f position;
    float radius;
    bool isChoosen;
    sf::Color color = sf::Color::White;
};