#include <vb.hpp>
#include <cmath>
#include <stdarg.h>


const vb::Transform vb::Transform::Zero = {0,0,0,0};
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
const sf::Color VB_GREEN     = sf::Color(108, 161, 59);
const sf::Color VB_RED       = sf::Color(255, 101, 74);
const sf::Color VB_WHITE     = sf::Color(229, 240, 225);
const sf::Color VBC_BG       = sf::Color(30, 34, 36);



const vb::Time vb::current_time(){
	std::time_t sinceEpoch = std::time(nullptr);
	std::tm t = *std::localtime(&sinceEpoch);
	return vb::Time(t.tm_hour, t.tm_min);
}


// takes path string literal and returns it without the tail
const char* vb::rtrim(const char* s, size_t len, const char target){
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



float vb::distance(const sf::Vector2f& A, const sf::Vector2f& B){
	return std::hypot(A.x - B.x, A.y - B.y);
}


sf::Vector2f vb::get_intermediate_position(const sf::Vector2f& A, const sf::Vector2f& B, float n){
	float xn = A.x + n * (B.x - A.x);
	float yn = A.y + n * (B.y - A.y);
	return {xn, yn};
}


uint8_t vb::get_intermediate_int(const uint8_t& source, const uint8_t& target, const float& n){
	return (target-source) * n + source;
}

std::string vb::trimmable(const std::string &s, int maxlen){
	if (s.length() > maxlen) return s.substr(0,maxlen)+"..";
	else return s;
}

std::string vb::ltrim(const std::string &s){
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string vb::rtrim(const std::string &s){
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string vb::trim(const std::string &s){
    return vb::rtrim(vb::ltrim(s));
}


void vb::round_position(sf::Transformable *thing){
	sf::Vector2f pos = thing->getPosition();
	thing->setPosition(round(pos.x), round(pos.y));
}

void vb::round_origin(sf::Transformable *thing){
	sf::Vector2f origin = thing->getOrigin();
	thing->setOrigin(round(origin.x), round(origin.y));
}



const char* vb::get_resource(const char* filename){
	char* pth = new char[100];
	std::strcat(pth, "res/");
	std::strcat(pth, filename);
	return pth;
}


const char* vb::get_image(const char* filename){
	char* pth = new char[100];
	std::strcat(pth, "res/images/");
	std::strcat(pth, filename);
	return pth;
}





