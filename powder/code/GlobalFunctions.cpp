#include "GlobalFunctions.h"

bool keypress(sf::Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(key);
}

std::string numtostr(double number) {
	std::stringstream ss;
	ss << number;
	std::string ans = ss.str();
	return ans;
}
std::string DelSpace(std::string s) {
	std::string ans = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != ' ') {
			std::string temp = " ";
			temp[0] = s[i];
			ans = ans + temp;
		}
	}
	return ans;
}
std::string touppercase(std::string s) {
	for (int i = 0; i < s.size(); i++)
		s[i] = toupper(s[i]);
	return s;
}
bool StringCheck(std::string a, std::string b) {
	a = DelSpace(a);
	b = DelSpace(b);
	if (touppercase(a) == touppercase(b))
		return true;
	else
		return false;
}
int WordNum(std::string s) {
	int ans = 0;
	bool IsWord = false;
	s = s + " ";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ' && IsWord) {
			ans++;
			IsWord = false;
		}
		if (s[i] != ' ' && !IsWord) {
			IsWord = true;
		}
	}
	return ans;
}
std::string Word(std::string s, int n) {
	int a = 1;
	std::string ans = "";
	bool IsWord = false;
	s = " " + s + " ";
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == ' ' && IsWord) {
			a++;
			IsWord = false;
		}
		if (s[i] != ' ' && !IsWord) {
			if (a == n) {
				int j = i;
				std::string temp = " ";
				while (s[j] != ' ') {
					temp[0] = s[j];
					ans = ans + temp;
					j++;
				}
			}
			IsWord = true;
		}
	}
	return ans;
}
int GetNum(std::string s, int n) {
	std::string a = "";
	int c = 0;
	s += " ";
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i] <= '9' && s[i] >= '0') {
			c++;
			if (c == n) {
				int j = i;
				if (i > 0 && s[i - 1] == '-') {
					std::string temp = " ";
					temp[0] = s[j];
					a += temp;
				}
				while (s[j] <= '9' && s[j] >= '0') {
					std::string temp = " ";
					temp[0] = s[j];
					a += temp;
					j++;
				}
				break;
			}
			else
				while (s[i] <= '9' && s[i] >= '0')
					i++;
		}
	}
	if (a != "")
		return atoi(a.c_str());
	else
		return -1;
}
bool WordCheck(std::string a, std::string word) {
	int n = WordNum(a);
	for (int i = 1; i <= n; i++) {
		if (StringCheck(word, Word(a, i)))
			return true;
	}
	return false;
}
