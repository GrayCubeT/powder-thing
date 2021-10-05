#include <algorithm>
#include <stdio.h>
#define NOMINMAX
#include <Windows.h>
#include <math.h>
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
#include "GlobalFunctions.h"
#include "Vect.h"
#include "classes.h"

using namespace sf;

const int MAXPARTICLES = 100000;
const int PARTICLESCREATED = 100;
const int MAXSUNS = 100;
const double STARTRANDMULT = 0.0;
const double STARTSPEEDMULT = 0.995;


int main() {
	std::string textflag = "";
	Font font;
	double Btimer = 0;
	bool lmb = false, rmb = false, paused = false, pull = false, stop = false, rmbmoveflag = true;
	double speedmult = STARTSPEEDMULT;
	double randmult = STARTRANDMULT;
	simpleparticle *particles;
	int partnum = 0;
	sunparticle *suns;
	int sunnum = 0;
	vect mpos, prevmpos;
	RenderWindow win(VideoMode::getDesktopMode(), "Ah yes, enslaved pixels", Style::Fullscreen);
	VertexArray dots;
	VertexArray suntri;
	vect clientsize = vect(Vector2f(win.getSize()));
	vect randv;
	View fixedview = win.getDefaultView();
	View view = win.getDefaultView();
	double screenratio = clientsize.y / clientsize.x;
	double shiftmult = 1;
	double currentspeed;
	Text text = Text("", font);
	text.setFillColor(Color::Magenta);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color::White);
	Text text1 = text, text2 = text, text3 = text, text4 = text;
	text.setPosition(5, 0);
	text1.setPosition(5, 30);
	text2.setPosition(5, 60);
	text3.setPosition(5, clientsize.y - 40);
	text4.setPosition(700, clientsize.y - 40);

	srand(time(0));
	if (!font.loadFromFile("virgo.ttf")) {
		std::cout << "font not loaded, exiting";
		Sleep(10000);
		return 0;
	}
	win.setFramerateLimit(60);
	particles = new simpleparticle[MAXPARTICLES];
	suns = new sunparticle[MAXSUNS];
	dots.setPrimitiveType(PrimitiveType::Points);
	dots.clear();
	dots.resize(MAXPARTICLES);
	suntri.setPrimitiveType(PrimitiveType::Triangles);
	suntri.clear();
	suntri.resize(MAXSUNS * 3);


	for (int i = 0; i < MAXPARTICLES; i++) {
		dots[i].position = Vector2f(-4000, -4000);
	}
	for (int i = 0; i < MAXSUNS * 3; i++) {
		suntri[i].position = Vector2f(-4000, -4000);
	}
	while (win.isOpen()) {
//conlrols
		//events
		Event event;
		while (win.pollEvent(event)) {
			if (event.type == Event::Closed) {
				win.close();
				break;
			}
			if (event.type == Event::MouseWheelScrolled) {
				if (textflag == "speedmult") {
					speedmult += 0.001 * event.mouseWheelScroll.delta * shiftmult;
				}
				if (textflag == "randmult") {
					randmult += 0.1 * event.mouseWheelScroll.delta * shiftmult;
				}
				if (textflag == "") {
					view.setSize(view.getSize() + Vector2f(-100 * shiftmult * event.mouseWheelScroll.delta, -100 * shiftmult * screenratio * event.mouseWheelScroll.delta));
				}
			}
		}
		//mouse handling
		{
			mpos = vect(win.mapPixelToCoords(Mouse::getPosition()));
			lmb = (sf::Mouse::isButtonPressed(sf::Mouse::Left));
			rmb = (sf::Mouse::isButtonPressed(sf::Mouse::Right));
		}
		//specific keypresses
		{
			//pause
			if (keypress(Keyboard::Escape)) {
				if (Btimer <= 1) {
					paused = !paused;
					Btimer = 200;
				}
			}
			
			//shift
			if (keypress(Keyboard::LShift)) {
				shiftmult = 10;
			}
			else {
				shiftmult = 1;
			}
			//camera movement
			if (keypress(Keyboard::A)) {
				view.move(-5 * shiftmult, 0);
			}
			if (keypress(Keyboard::D)) {
				view.move(5 * shiftmult, 0);
			}
			if (keypress(Keyboard::W)) {
				view.move(0, -5 * shiftmult);
			}
			if (keypress(Keyboard::S)) {
				view.move(0, 5 * shiftmult);
			}
			if (rmb) {
				if (rmbmoveflag) {
					prevmpos = mpos;
					rmbmoveflag = false;
				}
				else {
					view.move(-mpos.x + prevmpos.x, -mpos.y + prevmpos.y);
				}
			}
			else {
				rmbmoveflag = true;
			}
			//zoom
			if (keypress(Keyboard::Z)) {
				view.setSize(view.getSize() + Vector2f(10 * shiftmult, 10 * screenratio * shiftmult));
			}
			if (keypress(Keyboard::X)) {
				view.setSize(view.getSize() + Vector2f(-10 * shiftmult, -10 * screenratio * shiftmult));
			}
			
			//particle creation
			if (lmb) {
				if (partnum < MAXPARTICLES - PARTICLESCREATED) {
					for (int i = 0; i < PARTICLESCREATED; i++) {
						dots[partnum + i].position = Vector2f(mpos.x + (rand() % 1001 - 500) / 25.0, mpos.y + (rand() % 1001 - 500) / 25.0);
						particles[partnum + i].sfr = &dots[partnum + i].position;
					}
					partnum += PARTICLESCREATED;
				}

			}
			if (keypress(Keyboard::F) && Btimer < 1) {
				if (sunnum < MAXSUNS - 1) {
					suntri[sunnum * 3].position = Vector2f(mpos.x, mpos.y - 4.666);
					suntri[sunnum * 3 + 1].position = Vector2f(mpos.x - 4, mpos.y + 2.333);
					suntri[sunnum * 3 + 2].position = Vector2f(mpos.x + 4, mpos.y + 2.333);
					suns[sunnum].r = mpos;
					suns[sunnum].fixed = true;
					suns[sunnum].mass = 1;
					sunnum++;
				}
				Btimer = 100;
			}

			//reset all
			if (keypress(Keyboard::R) && Btimer < 1) {
				Btimer = 200;
				for (int i = 0; i < partnum; i++) {
					dots[i].position = Vector2f(-4000, -4000);
					if (shiftmult == 1) // saving with shift pressed [WARNING: SUPER FUCKING COOL]
						particles[i].v = vect();
				}
				for (int i = 0; i < sunnum; i++) {
					suntri[i * 3].position = Vector2f(-4000, -4000);
					suntri[i * 3 + 1].position = Vector2f(-4000, -4000);
					suntri[i * 3 + 2].position = Vector2f(-4000, -4000);
				}
				partnum = 0;
				sunnum = 0;

			}

		
			
			
			//pull
			if (keypress(Keyboard::E)) {
				pull = true;
			}
			else {
				pull = false;
			}
			//stop
			if (keypress(Keyboard::Q)) {
				stop = true;
			}
			else {
				stop = false;
			}
		}
//calculations
		//physics 
		if (!paused) {
			//simple particles
			for (int i = 0; i < partnum; i++) {
				//pull
				if (pull) {
					vect dist(mpos.x - (*particles[i].sfr).x, mpos.y - (*particles[i].sfr).y);
					particles[i].a = dist.copylength(0.9);
				}
				else { 

					particles[i].a = vect();
				}

				//pull to suns
				for (int j = 0; j < sunnum; j++) {
					vect dist(suns[j].r.x - (*particles[i].sfr).x, suns[j].r.y - (*particles[i].sfr).y);
					dist.setlength(suns[j].mass * 0.90);
					particles[i].a = particles[i].a + dist;
				}

				//random movement
				randv = vect(rand() % 101 - 50, rand() % 101 - 50);
				randv.setlength(randmult * 0.001);
				particles[i].v = particles[i].v + randv;

				if (stop) {
					particles[i].v = particles[i].v * 0.95;
				}
				particles[i].a.setlength(0.1);

				//[NOTE:not implemented]gravity to eachother

				//[NOTE:not implemented]electrostatics

				//speedmult
				particles[i].v = particles[i].v * speedmult;

				//calc function for particles
				(*particles[i].sfr) = (*particles[i].sfr) + Vector2f((particles[i].v.x * GLOBALVEL), (particles[i].v.y * GLOBALVEL));
				particles[i].v = particles[i].v + particles[i].a;

				//variable color
				currentspeed = particles[i].v.length();
				dots[i].color = Color(std::max(100 - currentspeed * 20, 0.1), std::min(50 + currentspeed * 50, 254.9), std::min(50 + currentspeed * 50, 254.9));
			}
			//suns
			for (int i = 0; i < sunnum; i++) {
				//fixed
				if (suns[i].fixed) {
					continue;
				}
				//pull
				if (pull) {
					vect dist = mpos - suns[i].r;
					suns[i].a = dist.copylength(1);
				}
				else {
					suns[i].a = vect();
				}

				//random movement [add variable rand mov]
				/*
				randv = vect(rand() % 101 - 50, rand() % 101 - 50);
				randv.setlength(0.00);
				suns[i].v = suns[i].v + randv;*/
				
				//stop
				if (stop) {
					suns[i].v = suns[i].v * 0.95;
				}

				//gravity between suns
				/*
				for (int j = 0; j < sunnum; j++) {
					if (j == i)
						continue;
					vect dist = vect(suns[j]->r - suns[i]->r);
					if (dist.length() > 50)
						dist.setlength(suns[i]->mass * suns[j]->mass * 500 / dist.length() / dist.length());
					else if (dist.length() != 0)
						dist.setlength(-suns[i]->mass * suns[j]->mass * 0.1 / dist.length());
					suns[i]->a = suns[i]->a + dist;
				}
				*/

				//speedmult
				suns[i].v = suns[i].v * speedmult;
				//calc function
				suns[i].r = suns[i].r + suns[i].v * GLOBALVEL;
				suns[i].v = suns[i].v + suns[i].a;
				vect _r = suns[i].r;
				//drawables adjustment
				suntri[sunnum * 3].position = Vector2f(_r.x, _r.y - 4.666);
				suntri[sunnum * 3 + 1].position = Vector2f(_r.x - 4, _r.y + 2.333);
				suntri[sunnum * 3 + 2].position = Vector2f(_r.x + 4, _r.y + 2.333);
			}
		}
		//other
		Btimer -= (1000 / 60);
//rendering
		win.clear();
		//text + buttons
		{
			win.setView(fixedview);
			text.setString(numtostr(mpos.x) + " " + numtostr(mpos.y));
			win.draw(text);

			text1.setString("p - " + numtostr(partnum));
			win.draw(text1);

			text2.setString("s - " + numtostr(sunnum));
			win.draw(text2);

			text3.setString("speedmult - " + numtostr(speedmult));
			if (text3.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) {
				textflag = "speedmult";
				text3.setFillColor(Color::Cyan);
				if (keypress(Keyboard::Add) && Btimer < 1) {
					speedmult += 0.001 * shiftmult;
					Btimer = 100;
				}
				if (keypress(Keyboard::Subtract) && Btimer < 1) {
					speedmult -= 0.001 * shiftmult;
					Btimer = 100;
				}
			}
			else {
				text3.setFillColor(Color::Magenta);
				if (textflag == "speedmult") {
					textflag = "";
				}
			}
			win.draw(text3);

			text4.setString("random movement multiplier - " + numtostr(randmult));
			if (text4.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) {
				textflag = "randmult";
				text4.setFillColor(Color::Cyan);
				if (keypress(Keyboard::Add) && Btimer < 1) {
					randmult += 0.1 * shiftmult;
					Btimer = 100;
				}
				if (keypress(Keyboard::Subtract) && Btimer < 1) {
					randmult -= 0.1 * shiftmult;
					Btimer = 100;
				}
			}
			else {
				text4.setFillColor(Color::Magenta);
				if (textflag == "randmult") {
					textflag = "";
				}
			}
			win.draw(text4);
		}
		//particles
		{
			win.setView(view);
			win.draw(dots);
			win.draw(suntri);
		}

		win.display();
//		
	}
}