#pragma once
#include <Entity.hpp>
#include <Stack.hpp>

// FD
struct Rack;


struct Chooser : public VStack {
	//
	// A vertical arrangment of buttons.
	//
	bool editing = false;
	std::vector<std::function<void(void)>> options;
	int select_index = 0;

	Chooser(){}
	Chooser(vb::Transform _tf, int _padding, bool _engaged = false);
	void engage(bool value);
	void refresh();
	void move_selector(vb::Direc dir);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};




