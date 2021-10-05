#pragma once
#include <math.h>
#include <string>
#include <algorithm>
#include <sstream>
#include "SFML\Graphics.hpp"

const double GLOBALVEL = 4;
const double PI = 3.14159265359;


bool keypress(sf::Keyboard::Key key);

std::string numtostr(double number);
std::string DelSpace(std::string s);
std::string touppercase(std::string s);
bool StringCheck(std::string a, std::string b);
int WordNum(std::string s);
std::string Word(std::string s, int n);
int GetNum(std::string s, int n);
bool WordCheck(std::string a, std::string word);

