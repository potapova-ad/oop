#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

bool check_point_rect_collision(const sf::Vector2i& p, const sf::RectangleShape& rect) {

    sf::Vector2f left_top_point = rect.getPosition() - rect.getOrigin();
    float left_x = left_top_point.x;
    float right_x  = left_top_point.x + rect.getSize().x;
    float left_y = left_top_point.y;
    float right_y  = left_top_point.y + rect.getSize().y;
    if (p.x > left_x && p.x < right_x && p.y > left_y && p.y < right_y)
        return true;
    return false;

}

class Point {
public:

	int x = 0; 
	int y = 0;

};

class Color {
public:

	char r;
	char g; 
	char b;


};

class Button {
public:

	Button(Point ldp, Point rup, Color color, void (*ex)()) {

		sf::RectangleShape rectangle({rup.x - ldp.x, rup.y - ldp.y});
		rectangle.setFillColor({color.r, color.g, color.b});
		color_ = {color.r, color.g, color.b};
		rectangle.setPosition({(rup.x + ldp.x) / 2, (rup.y + ldp.y) / 2});
		rectangle.setOrigin({(rup.x - ldp.x) / 2, (rup.y - ldp.y) / 2});
		form = rectangle;
		ex_ = ex;

	}

	void pressed(sf::Event event, sf::RenderWindow *window) { 

		if (event.type == sf::Event::MouseButtonPressed) {
			bool flag = false;
			if (check_point_rect_collision(sf::Mouse::getPosition(*window), form)) {
				flag = true;
				form.setFillColor(sf::Color({color_.r, color_.g + 70, color_.b}));
			}
			window->draw(form);
			window->display();
			while (event.type != sf::Event::MouseButtonReleased) window->pollEvent(event);
			if (flag && event.type == sf::Event::MouseButtonReleased && check_point_rect_collision(sf::Mouse::getPosition(*window), form))
				ex_();
			if (check_point_rect_collision(sf::Mouse::getPosition(*window), form)) {
				form.setFillColor(sf::Color({color_.r, color_.g , color_.b + 70}));
			}
			else form.setFillColor(sf::Color({color_.r, color_.g , color_.b}));
			window->draw(form);
			window->display();
		}
		else if (event.type == sf::Event::MouseMoved) {
			if (check_point_rect_collision(sf::Mouse::getPosition(*window), form)) {
				form.setFillColor(sf::Color({color_.r, color_.g , color_.b + 70}));
			}
			else form.setFillColor(sf::Color({color_.r, color_.g , color_.b}));
		}
		else if (check_point_rect_collision(sf::Mouse::getPosition(*window), form)) {
				form.setFillColor(sf::Color({color_.r, color_.g , color_.b + 70}));
			}
			else form.setFillColor(sf::Color({color_.r, color_.g , color_.b}));
		window->draw(form);
		window->display();
	}

	Color color_;
	sf::RectangleShape form;
	void (*ex_)();

};