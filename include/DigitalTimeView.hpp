#pragma once
#include <SFML/Graphics.hpp>
#include <jb.hpp>
#include <Line.hpp>
#include <math.h>
#include <Entity.hpp>


enum Meridiem { ANTE, POST, MERIDIEM_N };


struct DigitalTimeView : public Entity {
	Line line;
	sf::Text semicolon;
	float lerp, lerp_target;
	int index;
	Meridiem meridiem;


	DigitalTimeView(){}
	DigitalTimeView(jb::Transform _tf);
	DigitalTimeView(const DigitalTimeView& other) = default;
	DigitalTimeView& operator =(const DigitalTimeView& from) = default;

	void move_selector(int direction);
	void alter_digit(int direction);
	void switch_meridiem();
	jb::Time get_time();

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};
