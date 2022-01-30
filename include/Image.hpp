#pragma once
#include <Entity.hpp>


struct Image : public Entity {
	sf::Image image;
	sf::Texture tex;
	sf::Sprite sprite;
		
	Image(vb::Transform _tf, const char* filename);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




