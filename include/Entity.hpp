#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


struct Entity : public sf::Drawable {
	jb::Transform tf;

	Entity(){}
	Entity(jb::Transform _tf)
		: tf(_tf)
	{
	}

	Entity(const Entity& other) = default;

	//virtual ~Entity(){};
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(){
		std::cout << "'update' not defined for this child" << std::endl;
	}
	virtual void engage(bool value) {
		std::cout << "'engage' not defined for this child" << std::endl;
	}
};

