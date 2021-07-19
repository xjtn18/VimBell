#include <Menu.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>
#include <sstream>


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
		std::ostringstream ss;
		ss << std::right << std::setw(8) << (std::string) alarms[i].target
			<< "    " << alarms[i].msg;
		auto* new_cell = new AlarmCell({0, 0, tf.w, 45}, ss.str());
		if (i == rack_state->select_index){
			new_cell->engage(engaged);
		}
		insert(-1, new_cell); // Stack::insert
	}
}


void Menu::update(float dt){
   VStack::update(dt);
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	VStack::draw(target, states);
}


bool Menu::handler(sf::Event& event, Program& p){
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
			return true;


		case sf::Keyboard::K: // move rack selector up
			if (LSHIFT_IS_DOWN){
				p.rack->set_select(0);
				refresh();
			} else {
				p.rack->select_move(jb::UP);
				refresh();
			}
			return true;


		case sf::Keyboard::Enter: // duplicate currently selected alarm
			p.rack->add_to_stack();
			refresh();
			return true;


		case sf::Keyboard::Backspace: // remove alarm from rack
			{
				bool last_in_stack = p.rack->remove_from_stack();

				if (last_in_stack){
					auto confirm_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
															"Delete this alarm ("+p.rack->get_selection_message()+")?");
					confirm_popup->yes_routine = [&](){
						p.rack->remove_alarm();
						refresh();
						p.draw_list.pop_back(); // destroy popup
						if (p.rack->size() == 0){
							p.engage_with(p.main_tbox); // engage the text field
						} else {
							p.engage_with(this); // engage the rack again
						}
					};

					confirm_popup->no_routine = [&](){
						p.draw_list.pop_back(); // destroy popup
						p.engage_with(this); // engage the rack again
					};

					p.draw_list.push_back(confirm_popup);
					p.engage_with(confirm_popup);
				}
			}
			refresh();
			return true;

		case sf::Keyboard::T: // toggle alarm active state
			p.rack->toggle_selection();
			refresh();
			return true;

		case sf::Keyboard::W: // increment duplicate time adjustment
			if (LALT_IS_DOWN){
				p.rack->adjust_dup_increment(5);
				return true;
			}
			return false;

		case sf::Keyboard::S: // decrement duplicate time adjustment
			if (LALT_IS_DOWN){
				p.rack->adjust_dup_increment(-5);
				return true;
			}
			return false;

		case sf::Keyboard::E: // edit alarm
			p.main_tbox->fill(p.rack->get_selection_message());
			p.engage_with(p.main_tbox);
			editing = true;
			return true;

		case sf::Keyboard::Tab: // switch modes
			p.engage_with(p.main_tbox);
			return true;
		}
	}
	return false;
}



