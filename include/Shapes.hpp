#pragma once
#include <jb.hpp>


struct BorderedRect : public Entity {

	sf::RectangleShape rect;

	BorderedRect(jb::Transform _tf, int bw)
		: Entity(_tf)
	{
		rect.setSize({(float)tf.w - bw * 2, (float)tf.h - bw * 2});
		rect.setOrigin(-bw, -bw);
		rect.setFillColor(sf::Color(50,50,50));

		rect.setOutlineThickness(bw);
		rect.setOutlineColor(sf::Color(150,150,150));
	}


	void update(float dt){
		rect.setPosition(tf.x, tf.y);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(rect);
	}

};



struct LineShape : public Entity {

	sf::RectangleShape line;

	LineShape(jb::Transform _tf)
		: Entity(_tf)
	{
		line.setOrigin(_tf.w/2, _tf.h/2);
		line.setFillColor(JB_GREEN);
		line.setSize({(float)tf.w, (float)tf.h});
	}

   void update(float dt){
		line.setPosition(tf.x, tf.y);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(line);
	}

};


