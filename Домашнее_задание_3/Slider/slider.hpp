#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Slider {

public:

    Slider(sf::RenderWindow &window_, sf::Font &font, sf::Vector2f position, sf::Vector2f size_, sf::Color color) {

        font.loadFromFile("consolas.ttf");
        current_state = size.x;
        size = (sf::Vector2i)size_;
        window  = &window_;
        color = color;
        last_mouse_position = {-1, -1};
        number.setFont(font);
        number.setFillColor(color_1);
        number.setCharacterSize(font_size);
        number.setPosition({(float)(position.x + bwidth + 2 * width), (float)(position.y)});
        number.setString(std::to_string(current_state));
        body.setFillColor(color);
        body.setPosition(position + sf::Vector2f({0, (float)height / 2 - (float)bheight / 2})); 
        body.setSize({(float)bwidth, (float)bheight});
        slider.setFillColor(color);
        slider.setPosition(position);
        slider.setSize({(float)(width), (float)(height)});
    }

    void catchEvent(const sf::Event &event) {

        if (event.type == sf::Event::MouseButtonPressed) {

            sf::Vector2f mousePosition = window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            
            if (isInSlider(mousePosition)) {

                isScrolling_ = true;

            }
        }

        if (event.type == sf::Event::MouseMoved && isScrolling_) {

            sf::Vector2f mousePosition = window->mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            
                if (last_mouse_position.x == -1 && last_mouse_position.y == -1) {

                    last_mouse_position = mousePosition;

                }
                
                sf::Vector2f shiftv = {mousePosition.x - last_mouse_position.x, 0};
                slider.setPosition(slider.getPosition() + shiftv);
                isInBody();
                last_mouse_position = mousePosition;
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            isScrolling_ = false;
        }

    }

    bool isInSlider(sf::Vector2f point) {

        sf::Vector2f p = slider.getPosition();
        sf::Vector2f bp {(float)__INT32_MAX__, (float)__INT32_MAX__};
        sf::Vector2f tp { 0, 0};
        sf::Vector2f points[4];
        for (int i = 0; i < 4; ++i) {
            
            points[i] = p + slider.getPoint(i);

        }

        for (int i = 0; i < 4; ++i) {

            if (points[i].x < bp.x || points[i].y < bp.y) bp = points[i];
            if (points[i].x > tp.x || points[i].y > tp.y) tp = points[i];

        }

        return ((point.x > bp.x && point.x < tp.x) && (point.y > bp.y && point.y < tp.y));
        
    }

    void isInBody() {

        sf::Vector2f left  = body.getPoint(0) + body.getPosition();
        sf::Vector2f right = body.getPoint(1) + body.getPosition();
        sf::Vector2f cur = slider.getPosition();
        if (cur.x < left.x) {
            
            slider.setPosition({left.x, slider.getPosition().y});

        }

        if (cur.x > right.x) {
            
            slider.setPosition({right.x, slider.getPosition().y});

        }

        current_state = int((float)(slider.getPosition().x - body.getPosition().x ) / bwidth * (size.y - size.x) + size.x);

    }

    void draw() {

        window->draw(body);
        window->draw(slider);
        number.setString(std::to_string((int)current_state));

        window->draw(number);
    }

    float getCurrentValue() const{
        
        return current_state;
    }
    
private:

    sf::RenderWindow *window; 
    sf::RectangleShape slider; 
    sf::RectangleShape body;
    sf::Vector2i size;
    sf::Text number;      
    sf::Color color;       
    sf::Vector2f last_mouse_position; 
    float current_state;   
    bool isScrolling_ = false;
    inline static const sf::Color color_1 {sf::Color(100, 100, 100)};
    inline static const int height = 30;
    inline static const int width  = 10;
    inline static const int bwidth = 300;
    inline static const int bheight = 10;
    inline static const int font_size = 20;

};