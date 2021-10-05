#include "vect.h"


vect::vect() {
	x = 0;
	y = 0;
}
vect::vect(double _x, double _y) {
	x = _x;
	y = _y;
}
vect::vect(sf::Vector2f _v) {
	x = _v.x;
	y = _v.y;
}
vect::vect(sf::Vector2i _v) {
	x = _v.x;
	y = _v.y;
}
vect::~vect() {

}
const vect vect::operator+(const vect& a) const{
	return vect(x + a.x, y + a.y);
}
const vect vect::operator=(const vect& a) {
	x = a.x;
	y = a.y;
	return a;
}
const vect vect::operator*(const double& a) const{
	return vect(x * a, y * a);
}
const vect vect::operator-(const vect& a) const
{
	return vect(x - a.x, y - a.y);
}
const vect vect::operator/(const double& a) const {
	return vect(x / a, y / a);
}
double vect::length() const {
	return sqrt(x * x + y * y);
}
void vect::setlength(double l) {
	if (length() != 0)
		*this = *this / length() * l;
}
vect vect::copylength(double l) const{
	if (length() != 0)
		return (*this / length() * l);
	return vect();
}
double degree(vect a, vect b) {
	double a2 = scalar(a, b) / (a.length() * b.length());
	if (cross(a, b) >= 0)
		return acos(a2);
	else
		return -acos(a2);

}
double scalar(const vect a, const vect b) {
	return (a.x * b.x + a.y * b.y);
}
double cross(const vect a, const vect b) {
	return (a.x * b.y - a.y * b.x);
}
vect nor(const vect a) {
	return vect(-a.y, a.x);
}