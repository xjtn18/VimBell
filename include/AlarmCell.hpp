#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <thread>

#include <Debug.hpp>
#include <Entity.hpp>


class AlarmCell: public Entity {

public:
	// UI
	AlarmCell(jb::Transform _tf, const std::string _text);

	static void cleanup();
	void set_pos();
	void set_color(sf::Color c);

	void engage(bool value);
	void deselect();
	void activate();
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Text bText;
	sf::String text;
	sf::Text stacc_indicator;

	bool is_hovered = false;
	static sf::Color idleColor, hoverColor;
	float lerp = 0;
	float rate = 0.025;
};


