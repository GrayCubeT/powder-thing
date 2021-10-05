#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <math.h>

class vect {
public:
	double x, y;

	vect();
	vect(double x, double y);
	vect(sf::Vector2f);
	vect(sf::Vector2i);
	~vect();

	const vect operator+(const vect& a) const;
	const vect operator=(const vect& a);
	const vect operator*(const double& a) const;
	const vect operator-(const vect& a) const;
	const vect operator/(const double& a) const;
	double length() const;
	void setlength(double l);
	vect copylength(double l) const;
};
double degree(const vect a, const vect b);
double cross(const vect a, const vect b);
double scalar(const vect a, const vect b);
vect nor(const vect a);
