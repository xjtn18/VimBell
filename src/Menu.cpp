#include <Menu.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>


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
	refresh();
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


void Menu::handler(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::J: // move rack selector down
			if (LSHIFT_IS_DOWN){
				p.rack->set_select(p.rack->size()-1);
				refresh();
			} else {
				p.rack->select_move(jb::DOWN);
				refresh();
			}
			break;

		case sf::Keyboard::K: // move rack selector up
			if (LSHIFT_IS_DOWN){
				p.rack->set_select(0);
				refresh();
			} else {
				p.rack->select_move(jb::UP);
				refresh();
			}
			break;

		case sf::Keyboard::Enter: // duplicate currently selected alarm
			p.rack->duplicate_alarm();
			refresh();
			break;

		case sf::Keyboard::Backspace: // remove alarm from rack
			/*
			{
				auto confirm_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
														"Delete this alarm ("+p.rack->get_selection_message()+")?");
				p.draw_list.push_back(confirm_popup);
			}
			*/
			p.rack->remove_alarm();
			if (p.rack->size() == 0){
				p.engage_with((Entity**)&(p.main_tbox));
			}
			refresh();
			break;

		case sf::Keyboard::T: // toggle alarm active state
			p.rack->toggle_selection();
			refresh();
			break;

		case sf::Keyboard::W: // increment duplicate time adjustment
			p.rack->adjust_dup_increment(5);
			break;

		case sf::Keyboard::S: // decrement duplicate time adjustment
			p.rack->adjust_dup_increment(-5);
			break;

		case sf::Keyboard::E: // edit alarm
			p.main_tbox->fill(p.rack->get_selection_message());
			p.engage_with((Entity**)&(p.main_tbox));
			p.editing = true;
			break;

		case sf::Keyboard::Tab: // switch modes
			p.engage_with((Entity**)&(p.main_tbox));
			break;
		}
	}
}
