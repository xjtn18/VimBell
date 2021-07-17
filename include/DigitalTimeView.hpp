#pragma once
#include <SFML/Graphics.hpp>
#include <jb.hpp>
#include <Line.hpp>
#include <math.h>
#include <Entity.hpp>
#include <Speaker.hpp>
using namespace aud;


enum Meridiem { ANTE, POST };


struct DigitalTimeView : public Entity {
	static Speaker *clock_speaker;
	static void cleanup();


	Line line;
	sf::CircleShape top_arrow, bottom_arrow;
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

	void engage(bool value);
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};
