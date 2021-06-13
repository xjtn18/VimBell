#pragma once
#include <SFML/Graphics.hpp>
#include <jb.hpp>


struct BorderedRect : public Entity {

	//
	int bw; // border width
	sf::RectangleShape rect;
	//


	BorderedRect(jb::Transform _tf, int _bw)
		: Entity(_tf),
		  bw(_bw)
	{
		rect = sf::RectangleShape({(float)tf.w - _bw * 2, (float)tf.h - _bw * 2});
		rect.setOrigin(-bw, -bw);
		rect.setFillColor(sf::Color(50,50,50));

		rect.setOutlineThickness(bw);
		rect.setOutlineColor(sf::Color(150,150,150));
	}


	void update(){
		std::cout << "bordered_rect update" << std::endl;
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(rect);
	}

};

