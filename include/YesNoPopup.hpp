#pragma once
#include <Entity.hpp>
#include <Stack.hpp>
#include <functional>


// FD
struct Text;


struct YesNoPopup : public Entity {
	sf::Text question;
	Text *option_yes, *option_no;
	sf::RectangleShape box, dimmer;
	HStack answers;
	std::function<void(void)> yes_routine = [](){};
	std::function<void(void)> no_routine = [](){};
	
	YesNoPopup(vb::Transform _tf, const std::string& _question);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};



