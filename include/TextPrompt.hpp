#pragma once
#include <TextField.hpp>


// FD
namespace aud {
	struct Speaker;
}


struct TextPrompt : public TextField {
	sf::RectangleShape dimmer;
	std::function<void(std::string)> submit = [](std::string s){};

	TextPrompt(vb::Transform _tf, const char* init_content, bool _engaged);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool handler(sf::Event& event, Program& p) override;
};


