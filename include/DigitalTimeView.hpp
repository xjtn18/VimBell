#pragma once
#include <SFML/Graphics.hpp>
#include <jb.hpp>
#include <Line.hpp>
#include <math.h>


struct DigitalTimeView : public sf::Drawable {
	static sf::Font font;
	jb::Transform tf;
	Line line;
	sf::Text semicolon;
	float lerp, lerp_target;

	DigitalTimeView(jb::Transform _tf);
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
