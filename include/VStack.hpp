#pragma once
#include <Entity.hpp>
#include <initializer_list>
#include <SFML/Graphics.hpp>


struct VStack : public sf::Drawable {
	int padding;
	std::vector<Entity*> entities;


	VStack(){};
	VStack(int x, int y, int _padding, std::initializer_list<Entity*> l);
	~VStack();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};



