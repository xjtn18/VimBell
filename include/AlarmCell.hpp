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
	sf::Color idleColor = sf::Color(231, 146, 71, 255);
	sf::Color hoverColor = sf::Color(132, 231, 47, 255);
	sf::Text bText;
	sf::String text;

	bool is_hovered = false;
	static sf::Font font;


public:
	static void setup();
	AlarmCell(int _w, int _h, const std::string _text);
	AlarmCell(const AlarmCell& other); // copy constructor
	AlarmCell& operator =(const AlarmCell& other); // assignment operator
	static void cleanup();
	void set_xy(int _x, int _y);
	int get_width() const;
	int get_height() const;
	void set_color(sf::Color c);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void select();
	void deselect();
	void activate();

};


