#include <iostream>
#include "point.h"
#include "circle.hpp"

int main() {

	Point p = {7, -1};
	Point q = {-4, 2};
	std::cout << "Point p = " << p << std::endl;
	std::cout << "Point q = " << q << std::endl;
	std::cout << "p + q = " << p + q << std::endl;

	Circle a {{4, 1}, 3};
	Circle b;

	std::cout << "Circle a: center: " << a.getCenter() << " radius: " << a.getRadius() << std::endl;
	std::cout << "Circle b: center: " << b.getCenter() << " radius: " << b.getRadius() << std::endl;

	std::cout << "Area of a = " << a.getArea() << std::endl;
	std::cout << "Distance from point p to circle a = " << a.getDistance(p) << std::endl;

	std::cout << "Collisions:" << std::endl;
	if (a.isColliding(b))
		std::cout << "Yes, a is colliding b" << std::endl;
	else
		std::cout << "No, a isn't colliding b" << std::endl;



	std::cout << "Moving b by {1, 1}:" << std::endl;
	b.move({1, 1});
	if (a.isColliding(b))
		std::cout << "Yes, a is colliding b" << std::endl;
	else
		std::cout << "No, a isn't colliding b" << std::endl;

	return 0;

}
