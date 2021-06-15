#include <InputManager.hpp>
#include <Program.hpp>


InputManager::InputManager(Program *_p)
	: p(_p)
{
	
}


void InputManager::switch_mode(Mode _mode){
	bool value = (_mode == TEXT) ? true : false;
	p->main_tbox.engage(value);
	p->rack_view->engage(!value);
	p->mode = _mode;
	p->mode_switched = true;
}



void InputManager::handle_universal_input(sf::Event& event){
	// User clicked the windows close button
	if (event.type == sf::Event::Closed){
		p->running = false;
		return;

	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Space:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				Alarm::silence();
				p->univ_triggered = true;
			}
			break;

		case sf::Keyboard::Escape:
			if (!p->editing){
				if (!DEV){
					if (p->ask_yes_no("Are you sure you want to exit?")){p->running = false;}
				} else {
					p->running = false;
				}
				p->univ_triggered = true;
			}
			break;
		}
	}
}


void InputManager::handle_rack_mode(sf::Event& event){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::J:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				p->rack->set_select(p->rack->size()-1);
			} else {
				p->rack->select_move(jb::DOWN);
			}
			break;

		case sf::Keyboard::K:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				p->rack->set_select(0);
			} else {
				p->rack->select_move(jb::UP);
			}
			break;

		case sf::Keyboard::Enter:
			p->rack->duplicate_alarm();
			break;

		case sf::Keyboard::Backspace:
			p->rack->remove_alarm();
			if (p->rack->size() == 0){
				switch_mode(TEXT);
			}
			break;

		case sf::Keyboard::O:
			p->rack->toggle_selection();
			break;

		case sf::Keyboard::W:
			p->rack->adjust_dup_increment(5);
			break;

		case sf::Keyboard::S:
			p->rack->adjust_dup_increment(-5);
			break;

		case sf::Keyboard::E:
			p->main_tbox.fill(p->rack->get_selection_message());
			switch_mode(TEXT);
			p->editing = true;
			break;
		}

		if (event.key.code == sf::Keyboard::Tab){
			switch_mode(TEXT);
		}
	}
}



void InputManager::handle_text_mode(sf::Event& event){
	// for text events
	if (event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			p->main_tbox.write(event.text.unicode);
		}

		// for special key events
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Tab:
			if (!p->editing && p->rack->size() != 0){
				switch_mode(RACK);
			}
			break;

		case sf::Keyboard::Backspace:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				p->main_tbox.clear_buffer(true);
			} else {
				p->main_tbox.delete_char();
			}
			break;

		case sf::Keyboard::Return:
			if (p->editing == false){
				p->rack->add_alarm(p->main_tbox.get_buffer());
			} else {
				p->rack->edit_selection(p->main_tbox.get_buffer());
				p->editing = false;
			}
			p->main_tbox.clear_all();
			switch_mode(RACK);
			break;

		case sf::Keyboard::Left:
			p->main_tbox.shift_cursor(jb::UP);
			break;

		case sf::Keyboard::Right:
			p->main_tbox.shift_cursor(jb::DOWN);
			break;

		case sf::Keyboard::Escape:
			p->editing = false;
			p->main_tbox.clear_all();
			switch_mode(RACK);
		}
	}
}


