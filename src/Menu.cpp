#include <Menu.hpp>


Menu::Menu(jb::Transform _tf, int _padding, std::shared_ptr<Rack> _rack_state, bool _engaged)
	: VStack(_tf, _padding, {}),
	  rack_state(_rack_state)
{
	engaged = _engaged;
	refresh();
	VStack::update(0.0f);
}


void Menu::engage(bool value){
	engaged = value;
}


void Menu::refresh(){
	clear();
	auto alarms = rack_state->alarms;
	for (int i = 0; i < alarms.size(); ++i){
		auto* A = new AlarmCell({0,0,tf.w,60}, alarms[i].msg);
		insert(-1, A);
		if (i == rack_state->select_index){
			entities[i]->engage(engaged);
		}
	}
}


void Menu::update(float dt){
   VStack::update(dt);
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	VStack::draw(target, states);
}
