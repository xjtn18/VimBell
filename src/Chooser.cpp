#include <Chooser.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>
#include <AlarmCell.hpp>
#include <TextField.hpp>
#include <TextPrompt.hpp>
#include <sstream>
#include <iomanip>


Chooser::Chooser(jb::Transform _tf, int _padding, bool _engaged)
	: VStack(_tf, _padding, {})
{
	engaged = _engaged;
	VStack::update(0.0f);
}


void Chooser::engage(bool value){
	engaged = value;
	if (entities.size() == 0) return;
	if (value == true){
		entities[select_index]->engage(true);
	} else {
		entities[select_index]->engage(false);
	}
}


void Chooser::move_selector(jb::Direc dir){
	entities[select_index]->engage(false);
	select_index += dir;
	bool clamped = jb::clamp(select_index, 0, entities.size());
	entities[select_index]->engage(true);
}


void Chooser::update(float dt){
   VStack::update(dt);
}


void Chooser::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	VStack::draw(target, states);
}



bool Chooser::handler(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::J: // move selector down
			move_selector(DOWN);
			return true;

		case sf::Keyboard::K: // move selector up
			move_selector(UP);
			return true;

		case sf::Keyboard::Enter: // select
			options[select_index]();
			return true;
		}
	}
	return false;
}



