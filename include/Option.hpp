#pragma once
#include <Entity.hpp>

// FD
struct Text;


class Option: public Entity {

public:
	// UI
	Option(vb::Transform _tf, const std::string _text);

	static void cleanup();
	void set_pos();
	void set_color(sf::Color c);

	void engage(bool value);
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Text bText;
	sf::String text;

	bool is_hovered = false;
	static sf::Color idleColor, hoverColor;
	float lerp = 0;
	float rate = 0.025;
};


