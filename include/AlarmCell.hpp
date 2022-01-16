#pragma once
#include <Entity.hpp>

// FD
struct Text;


class AlarmCell: public Entity {

public:
	// UI
	AlarmCell(jb::Transform _tf, const std::string _text, int _stacc, int _interval);

	static void cleanup();
	void set_pos();
	void set_color(sf::Color c);

	void engage(bool value);
	void idle();
	void trigger();
	void idle_select();
	void trigger_select();
	void toggle();
	void activate();
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Text bText;
	sf::String text;
	Text *stacc_indicator;
	Text *stacc_interval_indicator;

	bool active = true;
	bool is_hovered = false;
	bool is_triggered = false;
	static sf::Color idleColor, hoverColor, hoverTriggered;
};


