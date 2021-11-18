#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "context_menu.hpp"

// Вспомогательные функции, вычисляет расстояние между двумя точками
float distance(sf::Vector2f start, sf::Vector2f finish) {
    return sqrtf((start.x - finish.x)*(start.x - finish.x) + (start.y - finish.y)*(start.y - finish.y));
}

// Вспомогательные функции, рисует линию на холсте окна window
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White) {
    sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}

enum cont_m {DELETE = 0, CREATE, RANDOM_COLOR, INCREASE, DECREASE};

// Вспомагательный класс, описывет шарик
// position - положение шарика; radius - радиус
// is_chosen - говорит о том, выбран ли шарик или нет

struct Ball {

    sf::Vector2f position;
    float radius;
    bool isChoosen;
    sf::Color ball_color = sf::Color::White;

    Ball(sf::Vector2f position, float radius) : position(position), radius(radius) {
        isChoosen = false;
    }

    // Метод, который рисует шарик на холсте окна window
    void draw(sf::RenderWindow& window) const {
        // Тут рисуем белый кружочек
        sf::CircleShape circle(radius);
        circle.setFillColor(ball_color);
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);

        // Если шарик выбран
        if (isChoosen) {
            // То рисуем "уголки"
            const float fraction = 0.7;
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - radius, position.y + radius * fraction});
            drawLine(window, {position.x - radius, position.y + radius}, {position.x - fraction * radius, position.y + radius});

            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius, position.y + radius * fraction});
            drawLine(window, {position.x + radius, position.y + radius}, {position.x + radius * fraction, position.y + radius});

            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius * fraction, position.y - radius});
            drawLine(window, {position.x + radius, position.y - radius}, {position.x + radius, position.y - radius * fraction});

            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius * fraction, position.y - radius});
            drawLine(window, {position.x - radius, position.y - radius}, {position.x - radius, position.y - radius * fraction});
        }
    }
    
    void is_in_selected_area (sf::RectangleShape &selectionRect) {

        sf::Vector2f p = selectionRect.getPosition();
        sf::Vector2f a {(float)__INT32_MAX__, (float)__INT32_MAX__};
        sf::Vector2f b {0, 0};
        sf::Vector2f points[4];

        for (int i = 0; i < 4; ++i) {
        
            points[i] = p + selectionRect.getPoint(i);
        
        }

        for (int i = 0; i < 4; ++i) {
            if (points[i].x < a.x || points[i].y < a.y) a = points[i];
            if (points[i].x > b.x || points[i].y > b.y) b = points[i];
        }

        if ((position.x > a.x && position.x < b.x) && (position.y > a.y && position.y < b.y)) {
        
             isChoosen = true;

        }

        else {

        isChoosen = false;

        }
    }
};


int main() {

    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select, Move, Delete!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    std::list<Ball> balls;
    std::list<Ball> copy_balls;
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color(150, 150, 240, 50));
    selectionRect.setOutlineColor(sf::Color(200, 200, 255));
    bool isSelecting = false;
    bool isMoving = false;
    sf::Vector2f lastMousePosition = {-1, -1};
    sf::Vector2f mcoord = {-1, -1};
    sf::Font font;
    if (!font.loadFromFile("consolas.ttf")) {
        std::cout << "Can't load button font" << std::endl;
    }
    std::vector<sf::String> context_menu {"Delete", "Create", "Random Color", "Increase", "Decrease"};
    ContextMenu contextMenu(window, font);
    for (const auto &temp: context_menu) {
        contextMenu.addButton(temp);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
                break;

            }
            
            int result = contextMenu.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {

                mcoord = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}) ;
            
            }

            switch (result) {

                case DELETE : {

                    auto iterator = balls.begin(), t = iterator;

                    while (iterator != balls.end()) {

                        if (iterator->isChoosen) {

                            t = std::next(iterator);
                            balls.erase(iterator);
                            iterator = t;

                        } 
                        
                        else {
                            
                            ++iterator;
                        }
                    }

                    break;
                }

                case CREATE: { 

                    balls.push_back(Ball(mcoord, 5 + rand() % 50));
                    break;
                }

                case RANDOM_COLOR: { 

                    sf::Color new_color = sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);

                    for (Ball &b : balls)

                        if (b.isChoosen) {

                            b.ball_color = new_color;
                        }

                    continue;
                }

                case INCREASE: { 

                    for (Ball &b : balls) 

                        if (b.isChoosen) {

                            b.radius *= 1.25;
                        }

                    continue;
                }

                case DECREASE: {

                    for (Ball &b : balls) 
                        if (b.isChoosen) {

                           b.radius /= 1.25;
                        }
                    continue;
                }

            }

            if (event.type == sf::Event::MouseMoved) {

                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});

                if (isSelecting) {

                    selectionRect.setSize(mousePosition - selectionRect.getPosition());

                    for (Ball &b: balls) {

                        b.is_in_selected_area (selectionRect);

                    }
                } 


                if (isMoving) {

                    sf::Vector2f shiftm = mousePosition - lastMousePosition;
                    lastMousePosition = mousePosition;

                    for (Ball &b : balls) {

                        if(b.isChoosen) {

                            b.position += shiftm;

                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {

                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

                if (event.mouseButton.button == sf::Mouse::Left) {

                    lastMousePosition = mousePosition;
                    
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {

                        for (Ball &b : balls) {

                            if (b.isChoosen && distance(mousePosition, b.position) < b.radius) { 

                                isMoving = true; 
                                break; 

                            }
                        }

                        if (!isMoving)
                            for (Ball &b : balls)
                                b.isChoosen = false;
                    }

                    for (Ball &b : balls) {

                        if (distance(mousePosition, b.position) < b.radius) {

                            b.isChoosen = true;
                            isMoving = true;
                            break;

                        }
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {

                        balls.push_back(Ball(mousePosition, 5 + rand() % 50));

                    }

                    if (!isMoving) {
                        
                        isSelecting = true;

                    }

                    selectionRect.setPosition(mousePosition);
                    selectionRect.setSize({0, 0});
                }
                lastMousePosition = mousePosition;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

                sf::Color new_color = sf::Color(rand() % 256, rand() % 256, rand() % 256);

                for (Ball &b : balls) {

                    if (b.isChoosen) b.ball_color = new_color;

                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                auto it = balls.begin(), temp = it;

                while (it != balls.end()) {

                    if (it->isChoosen) {

                        temp = std::next(it);
                        balls.erase(it);
                        it = temp;

                    } 
                    
                    else {
                        
                        ++it;
                    
                    }
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {

                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X) {

                    copy_balls.clear();
                    
                    for (Ball &b : balls) {

                        if (b.isChoosen) {

                            copy_balls.push_back(b);

                        }
                    }

                    auto iterator = balls.begin(), t = iterator;

                    while (iterator != balls.end()) {

                        if (iterator->isChoosen) {

                            t = std::next(iterator);
                            balls.erase(iterator);
                            iterator = t;

                        } 
                        
                        else {
                            
                            ++iterator;
                        
                        }
                    }

                    continue;
                }


                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C) {

                    copy_balls.clear();

                    for (Ball &b : balls) {

                        if (b.isChoosen) {

                            copy_balls.push_back(b);

                        }                        
                    }

                    continue;
                }

                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::V) {

                    for (Ball &b : balls) {

                        b.isChoosen = false;

                    }

                    for (Ball &b : copy_balls) {

                        balls.push_back(b);
                    
                    }
                }
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

                window.close();
                break;

            }


            if (event.type == sf::Event::MouseButtonReleased) {

                isSelecting = false;
                isMoving    = false;

            }
        }

        window.clear(sf::Color::Black);

        for (Ball &b : balls) {
            b.draw(window);
        }
 
        if (isSelecting) {
            window.draw(selectionRect);
        }

        contextMenu.draw();
        window.display();
    }

    return 0;
}