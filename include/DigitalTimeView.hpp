#pragma once
#include <SFML/Graphics.hpp>
#include <jb.hpp>
#include <Line.hpp>
#include <math.h>
#include <Entity.hpp>


struct DigitalTimeView : public Entity {
	Line line;
	sf::Text semicolon;
	float lerp, lerp_target;


	DigitalTimeView(){}
	DigitalTimeView(jb::Transform _tf);
	DigitalTimeView(const DigitalTimeView& other) = default;
	DigitalTimeView& operator =(const DigitalTimeView& from);


	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
