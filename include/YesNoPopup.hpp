#pragma once
#include <jb.hpp>
#include <Entity.hpp>
#include <Stack.hpp>
#include <Text.hpp>


struct YesNoPopup : public Entity {
	sf::Text question;
	Text *option_yes, *option_no;
	sf::RectangleShape box, dimmer;
	HStack answers;
	
	YesNoPopup(jb::Transform _tf, const std::string& _question);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
