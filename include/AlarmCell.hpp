#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <Debug.hpp>
#include <Speaker.hpp>
#include <cmath>
#include <thread>


class AlarmCell: public sf::Drawable {
	int x,y,w,h;
	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Text bText;
	sf::String text;

	bool is_hovered = false;
	static sf::Color idleColor, hoverColor;
	static sf::Font font;


public:
	static void setup();
	AlarmCell(int _w, int _h, const std::string _text);
	AlarmCell(const AlarmCell& other); // copy constructor
	AlarmCell& operator =(const AlarmCell& other); // assignment operator
	static void cleanup();
	void set_xy(int _x, int _y);
	void set_color(sf::Color c);
	int get_height() const;
	int get_width() const;

	void select();
	void deselect();
	void activate();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


