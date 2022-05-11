#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <string>
#include <memory>

#include <Debug.hpp>

#define PI 3.14159265
#define is_in(x,y)   y.find(x) != y.end()
#define not_in(x,y)  y.find(x) == y.end()
#define DEV false
#define SET std::unordered_set

#define LSHIFT_IS_DOWN sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
#define LCOMMAND_IS_DOWN sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem)
#define LALT_IS_DOWN sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)

//////
///////////////////////
//////////////////////////////////////////////////////////////////////
// Global Constants

// Fonts
extern sf::Font FONT_LIBMONO;
extern sf::Font FONT_LIBMONO_B;
void load_fonts();

// Window params
extern const float WINW;
extern const float WINH;
const float CENTER_WIN_X = WINW/2;
const float CENTER_WIN_Y = WINH/2;

// Colors
extern const sf::Color VB_GREEN;
extern const sf::Color VB_RED;
extern const sf::Color VB_WHITE;
extern const sf::Color VBC_BG;

//////////////////////////////////////////////////////////////////////
///////////////////////
//////



namespace vb {

	struct Transform {
		static const Transform Zero;

		float x,y,w,h;
	};


	struct Time {
		int hour;
		int minute;

		Time()
			: hour(0), minute(0)
		{ }

		Time(int hr, int mn)
			: hour(hr), minute(mn)
		{ }


		bool operator ==(const Time& other) const { // equals operator
			return minute == other.minute && hour == other.hour;
		}


		Time(const Time& other) // copy constructor
			: hour(other.hour), minute(other.minute)
		{ }


		Time& operator=(const Time& other){
			if (&other != this){
				hour = other.hour;
				minute = other.minute;
			}
			return *this;
		}


		Time(const std::string& time_str) // construct from string in format "hh:mm"
			: hour(std::stoi(time_str.substr(0,2))), minute(std::stoi(time_str.substr(3,5)))
		{ }


		Time operator +(const int& increment) const {
			std::time_t sinceEpoch = std::time(nullptr);
			std::tm startT = *std::localtime(&sinceEpoch);
			startT.tm_hour = this->hour;
			startT.tm_min = this->minute;
			std::time_t t = std::mktime(&startT) + increment * 60;
			std::tm newT = *std::localtime(&t);
			return Time(newT.tm_hour, newT.tm_min);
		}


		Time& operator +=(const int& increment) {
			*this = *this + increment;
			return *this;
		}


		bool operator <(const Time& other) const {
			if (this->hour < other.hour){
				return true;
			} else if (this->hour > other.hour){
				return false;
			} else { // same hour, distinguish by minute
				return this->minute < other.minute;
			}
		}


		friend std::ostream& operator <<(std::ostream& os, const Time& time){
			os << "Time(" << time.hour << "h, " << time.minute << "m)";
			return os;
		}


		operator std::string() const {
			std::string str;
			int hour_nonmilitary = (hour % 12 == 0) ? 12 : hour % 12;
			str += std::to_string(hour_nonmilitary) + ":";
			if (minute < 10){
				str += "0"; // add extra front zero
			}
			str += std::to_string(minute);
			str += (hour % 12 == hour) ? " am" : " pm";
			return str;
		}
	};


	enum Direc {
		UP = -1,
		TOP = 0,
		DOWN = 1,
		BOTTOM = 2
	};


	const Time current_time();
	const char* rtrim(const char* s, size_t len, const char target);
	const char* get_resource(const char* filename);
	const char* get_image(const char* filename);


	template <typename T, typename T2>
	bool clamp(T& value, T low, T2 _high){
		// clamps the value to the bounds given, returns true if value was constrained, false otherwise.
		float high = (float) _high; // @NOTE: if size_t is passed as T2, since it is unsigned, if high == low,
												// 'value' will be invalid
		if (value < low){
			value = low;
			return true;
		} else if (value >= high){
			value = (high - 1 >= low) ? high - 1 : high;
			return true;
		}
		return false;
	}

	template <typename T1, typename T2, typename T3>
	bool anim_clamp(T1& value, T2 low, T3 _high){
		// clamps the value to the bounds given, returns true if value was constrained, false otherwise.
		float high = (float) _high; // @NOTE: if size_t is passed as T2, since it is unsigned, if high == low,
												// 'value' will be invalid
		if (value < low){
			value = low;
			return true;
		} else if (value >= high){
			value = (high - 0.001 >= low) ? high - 0.001 : high;
			return true;
		}
		return false;
	}

	template <typename T>
	void set_fill_alpha(T& t, uint8_t a){
		sf::Color c = t.getFillColor();
		t.setFillColor(sf::Color(c.r, c.g, c.b, a));
	}

	template <typename T>
	void set_outline_alpha(T& t, uint8_t a){
		sf::Color c = t.getOutlineColor();
		t.setOutlineColor(sf::Color(c.r, c.g, c.b, a));
	}


	//
	// Rounding functions >>
	// Certain objects, like text, get blurry if their positioning is not discrete pixel values.
	// Rounding the position and origin will eliminate this issue.
	//

	void round_position(sf::Transformable *thing);
	void round_origin(sf::Transformable *thing);
	std::string trimmable(const std::string &s, int maxlen);

	std::string ltrim(const std::string &s);
	std::string rtrim(const std::string &s);
	std::string trim(const std::string &s);

	float distance(const sf::Vector2f& A, const sf::Vector2f& B);
	sf::Vector2f get_intermediate_position(const sf::Vector2f& A, const sf::Vector2f& B, float n);
	uint8_t get_intermediate_int(const uint8_t& source, const uint8_t& target, const float& n);

}


