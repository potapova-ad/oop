#pragma once

class Circle {

    public:

	Circle(const Point& acenter, float aradius);
	Circle();
	Point &getCenter();
	void setCenter(const Point &new_center);
	float getRadius() const;
	void setRadius(float new_radius);
	float getArea() const;
	float getDistance(const Point &p) const;
	bool isColliding(const Circle &c) const;
	void move(const Point &p);

	private:

	Point center;
	float radius;

};
