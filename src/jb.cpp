#include <jb.hpp>
#include <cmath>
#include <stdarg.h>


const jb::Transform jb::Transform::Zero = {0,0,0,0};
const char* jb::rootPath = nullptr;
const std::string WHITESPACE = " \n\r\t\f\v";

// Window params
const float WINW = 750;
const float WINH = 750;

// Fonts
sf::Font FONT_LIBMONO;
sf::Font FONT_LIBMONO_B;

#define _LOAD_TTF(font) font.loadFromFile("res/fonts/" + (std::string)#font + ".ttf")
// '#' is a stringify preproc command: returns string representation of the variable name

void load_fonts() {
	// macro expects font file base name and font variable name to be equivalent
	_LOAD_TTF(FONT_LIBMONO);
	_LOAD_TTF(FONT_LIBMONO_B);
}

// Colors
const sf::Color JB_GREEN     = sf::Color(108, 161, 59);
const sf::Color JB_RED       = sf::Color(255, 101, 74);
const sf::Color JB_WHITE     = sf::Color(229, 240, 225);
const sf::Color JBC_BG       = sf::Color(30, 34, 36);



const jb::Time jb::current_time(){
	std::time_t sinceEpoch = std::time(nullptr);
	std::tm t = *std::localtime(&sinceEpoch);
	return jb::Time(t.tm_hour, t.tm_min);
}


// takes path string literal and returns it sans tail
const char* jb::rtrim(const char* s, size_t len, const char target){
	size_t i = len-1;
	for (; i >= 0; i--){
		if (s[i] == target){ break; }
	}
	if (i < 0){ // tail is entire path
		return s;
	}
	char* res = new char[i+1];
	strncpy(res, s, i);
	res[i] = '\0';
	return res;
}



float jb::distance(const sf::Vector2f& A, const sf::Vector2f& B){
	return std::hypot(A.x - B.x, A.y - B.y);
}


sf::Vector2f jb::get_intermediate_position(const sf::Vector2f& A, const sf::Vector2f& B, float n){
	//float dist = distance(A, B);
	float xn = A.x + n * (B.x - A.x);
	float yn = A.y + n * (B.y - A.y);
	return {xn, yn};
}


uint8_t jb::get_intermediate_int(const uint8_t& source, const uint8_t& target, const float& n){
	return (target-source) * n + source;
}

std::string jb::trimmable(const std::string &s, int maxlen){
	if (s.length() > maxlen) return s.substr(0,maxlen)+"..";
	else return s;
}

std::string jb::ltrim(const std::string &s){
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string jb::rtrim(const std::string &s){
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string jb::trim(const std::string &s){
    return jb::rtrim(jb::ltrim(s));
}


void jb::round_position(sf::Transformable *thing){
	sf::Vector2f pos = thing->getPosition();
	thing->setPosition(round(pos.x), round(pos.y));
}

void jb::round_origin(sf::Transformable *thing){
	sf::Vector2f origin = thing->getOrigin();
	thing->setOrigin(round(origin.x), round(origin.y));
}



const char* jb::get_resource(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/");
	std::strcat(pth, filename);
	return pth;
}


const char* jb::get_image(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/images/");
	std::strcat(pth, filename);
	return pth;
}





