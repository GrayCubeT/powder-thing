#pragma once
#include "Vect.h"
#include "GlobalFunctions.h"
#include <math.h>
#include <iostream>
#include "SFML\Graphics.hpp"

class simpleparticle {
public:
	vect r = vect(), v = vect(), a = vect();
	sf::Vector2f *sfr;
	void calc();
	simpleparticle(); 
	~simpleparticle();
/*	sf::Color color;
//	double mass = 0;
	double charge = 0;
	bool fixed = true;
	void randmov(double mult);
	void randcolor();
	void speedcolor();*/
};
class sunparticle : public simpleparticle{
public:
	bool fixed = true;
	double mass = 1;
	sunparticle();
	~sunparticle();
};
