#include <Chooser.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>
#include <AlarmCell.hpp>
#include <TextField.hpp>
#include <sstream>
#include <iomanip>




Chooser::Chooser(jb::Transform _tf, int _padding, bool _engaged)
	: VStack(_tf, _padding, {})
{
	engaged = _engaged;
	refresh();
	VStack::update(0.0f);
}


void Chooser::engage(bool value){
	engaged = value;
	refresh();
}


void Chooser::refresh(){
	VStack::clear();
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

		case sf::Keyboard::J: // move rack selector down
			{
				++select_index;
				bool clamped = jb::clamp(select_index, 0, options.size());
				dlog(select_index);
				refresh();
			}
			return true;

		case sf::Keyboard::K: // move rack selector up
			{
				--select_index;
				bool clamped = jb::clamp(select_index, 0, options.size());
				dlog(select_index);
				refresh();
			}
			return true;

		case sf::Keyboard::Enter: // duplicate currently selected alarm
			options[select_index]();
			//refresh();
			return true;
		}
	}
	return false;
}



