#include <Menu.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>
#include <AlarmCell.hpp>
#include <TextField.hpp>
#include <Text.hpp>
#include <DigitalTimeView.hpp>
#include <algorithm>
#include <sstream>
#include <iomanip>


Menu::Menu(jb::Transform _tf, int _padding, std::shared_ptr<Rack> _rack_state, bool _engaged)
	: VStack(_tf, _padding, {}),
	  rack_state(_rack_state)
{
	engaged = _engaged;

	auto alarms = rack_state->alarms;
	for (int i = 0; i < alarms.size(); ++i){
		std::ostringstream ss;
		ss << std::right << std::setw(8) << (std::string) alarms[i].target
			<< "    " << alarms[i].msg;
		auto* new_cell = new AlarmCell({0, 0, tf.w, 45}, ss.str(), alarms[i].stacc, alarms[i].stacc_interval);
		if (i == rack_state->select_index){
			new_cell->engage(engaged);
		}
		VStack::insert(-1, new_cell);
	}
	VStack::update(0.0f);
}


void Menu::engage(bool value){
	entities[rack_state->select_index]->engage(value);
	engaged = value;
}


void Menu::trigger(std::vector<int> triggered){
	for (int &index : triggered){
		if (this->engaged && index == rack_state->select_index){
			((AlarmCell*) entities[index])->trigger_select();
		} else {
			((AlarmCell*) entities[index])->trigger();
		}
	}
}

void Menu::set_all_idle(){
	for (int i = 0; i < entities.size(); ++i){
		if (i != rack_state->select_index){
			((AlarmCell*) entities[i])->idle();
		} else {
			((AlarmCell*) entities[i])->idle_select();
		}
	}
}

void Menu::move_selector(jb::Direc dir){
	entities[rack_state->select_index]->engage(false);
	rack_state->select_move(dir);
	entities[rack_state->select_index]->engage(true);
}


void Menu::set_selector(int index){
	entities[rack_state->select_index]->engage(false);
	rack_state->set_select(index);
	entities[rack_state->select_index]->engage(true);
}


void Menu::add(Program &p){
	std::ostringstream ss;
	std::string message = p.main_tbox->get_buffer();
	if (!editing){
		if (rack_state->size() == 10) return;
		rack_state->add_alarm(p.main_digitime->get_time(), message);
		ss << std::right << std::setw(8) << (std::string) p.main_digitime->get_time()
			<< "    " << message;
		auto* new_cell = new AlarmCell({0, 0, WINW, 45}, ss.str(), 1, 1);
		insert(rack_state->select_index, new_cell); // Stack::insert

	} else {
		ss << std::right << std::setw(8) << (std::string) p.main_digitime->get_time()
			<< "    " << message;
		rack_state->edit_selection(message);
		AlarmCell *acell = (AlarmCell*)entities[rack_state->select_index];
		acell->bText.setString(ss.str());
		editing = false;
	}
	p.main_tbox->clear_all();
	p.engage_with(this);
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
			if (LSHIFT_IS_DOWN) set_selector(rack_state->size()-1);
			else move_selector(DOWN);
			return true;

		case sf::Keyboard::K: // move rack selector up
			if (rack_state->select_index == 0) p.engage_with(p.main_tbox);
			else if (LSHIFT_IS_DOWN) set_selector(0);
			else move_selector(UP);
			return true;


		case sf::Keyboard::Enter: // duplicate currently selected alarm
			{
				Alarm& a = rack_state->get_selection();
				AlarmCell *acell = (AlarmCell*)(entities[rack_state->select_index]);
				if (LSHIFT_IS_DOWN){
					a.alter_stacc_interval(1);
					acell->stacc_interval_indicator->set_text(std::to_string(a.stacc_interval));
				} else {
					a.add_to_stack();
					acell->stacc_indicator->set_text("x"+std::to_string(a.stacc));
				}
			}
			return true;


		case sf::Keyboard::Backspace: // remove alarm from rack
			{
				Alarm& a = p.rack->get_selection();
				AlarmCell *acell = (AlarmCell*)(entities[rack_state->select_index]);

				if (LSHIFT_IS_DOWN){
					a.alter_stacc_interval(-1);
					acell->stacc_interval_indicator->set_text(std::to_string(a.stacc_interval));
				} else {
					bool last_in_stack = a.remove_from_stack();
					acell->stacc_indicator->set_text("x"+std::to_string(a.stacc));

					if (last_in_stack){
						auto confirm_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
																"Delete this alarm?(\""+trimmable(p.rack->get_selection_message(),11)+"\")?");
						confirm_popup->yes_routine = [&](){
							remove(rack_state->select_index);
							rack_state->remove_alarm();
							if (std::all_of(entities.begin(), entities.end(), [](Entity *e){
										return (!((AlarmCell*)e)->is_triggered);
									}))
							{
								Alarm::silence();
							}

							p.draw_list.pop_back(); // destroy popup
							if (rack_state->size() == 0) p.engage_with(p.main_tbox); // engage the text field
							else p.engage_with(this); // engage the rack again
						};

						confirm_popup->no_routine = [&](){
							p.draw_list.pop_back(); // destroy popup
							p.engage_with(this); // engage the rack again
						};

						p.draw_list.push_back(confirm_popup);
						p.engage_with(confirm_popup);
					}
				}
			}
			return true;

		case sf::Keyboard::T: // toggle alarm active state
			{
				p.rack->toggle_selection();
				AlarmCell *ac = ((AlarmCell*)entities[rack_state->select_index]);
				ac->toggle();
				if (std::all_of(entities.begin(), entities.end(), [](Entity *e){
							return (!((AlarmCell*)e)->is_triggered);
						}))
				{
					Alarm::silence();
				}
			}

			return true;

		case sf::Keyboard::E: // edit alarm
			p.main_tbox->fill(p.rack->get_selection_message());
			p.engage_with(p.main_tbox);
			editing = true;
			return true;

		case sf::Keyboard::Tab: // switch modes
			if (LSHIFT_IS_DOWN){
				p.engage_with(p.main_tbox);
				return true;
			}
			return false;
		}
	}
	return false;
}



