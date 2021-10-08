#include <iostream>
#include <cmath>
#include "point.h"
#include "circle.hpp"

Circle::Circle(const Point& acenter, float aradius) : center(acenter), radius(aradius) {}
Circle::Circle(): center({}), radius(1.) {}

Point &Circle::getCenter() {
	return center;
}
float Circle::getRadius() const {
	return radius;
}

void Circle::setCenter(const Point &new_center) {
	center = new_center;
}

void Circle::setRadius(float new_radius) {
    if (new_radius > 0) {
        radius = new_radius;
    }
    else {
        radius = 0;
    }
}

float Circle::getArea() const {
	return M_PI * radius * radius;
}

float Circle::getDistance(const Point &p) const {
	return center.distance(p) - radius;
}

bool Circle::isColliding(const Circle &c) const {
    if (center.distance(c.center) <= c.getRadius() + radius) {
        return true;
    }
    else {
        return false;
    }
}

void Circle::move(const Point &p) {
	center = center + p;
}
