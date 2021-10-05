#include "classes.h"


simpleparticle::simpleparticle() {
}
simpleparticle::~simpleparticle() {
}
void simpleparticle::calc() {
	r = r + (v * GLOBALVEL);
	v = v + a;
}

sunparticle::sunparticle() {

}
sunparticle::~sunparticle() {

}

/*
void simpleparticle::randmov(double mult) {
	vect randv(rand() % 101 - 50, rand() % 101 - 50);
	randv.setlength(0.01);
	v = v + randv * mult;
}

void simpleparticle::randcolor() {
	color.r = (color.r + rand() % 5 - 2) % 255;
	color.g = (color.g + rand() % 5 - 2) % 155 + 100;
	color.b = (color.b + rand() % 5 - 2) % 155 + 100;
}

void simpleparticle::speedcolor() {
	color.r = std::min(100 + (v.length() / 100), 255.0);
	color.g = std::min(100 + (v.length() / 100), 255.0);
	color.b = 0;
}
*/