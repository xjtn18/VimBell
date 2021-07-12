#pragma once
#include <jb.hpp>
#include <Entity.hpp>
#include <Stack.hpp>
#include <Text.hpp>
#include <functional>


struct YesNoPopup : public Entity {
	sf::Text question;
	Text *option_yes, *option_no;
	sf::RectangleShape box, dimmer;
	HStack answers;
	std::function<void()> yes_routine, no_routine;
	
	YesNoPopup(jb::Transform _tf, const std::string& _question);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};



