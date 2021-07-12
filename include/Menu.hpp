#pragma once

#include <jb.hpp>
#include <AlarmCell.hpp>
#include <Debug.hpp>
#include <Rack.hpp>
#include <Entity.hpp>
#include <Stack.hpp>

#include <vector>
#include <initializer_list>


struct Menu : public VStack {
	//
	// A vertical arrangment of buttons.
	//
	std::shared_ptr<Rack> rack_state;
	bool editing = false;

	Menu(){}
	Menu(jb::Transform _tf, int _padding, std::shared_ptr<Rack> _rack_state, bool _engaged = false);
	void engage(bool value);
	void refresh();

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);
};




