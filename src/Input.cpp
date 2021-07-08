#include <Input.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>


#define LSHIFT_IS_DOWN sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)



void switch_mode(Mode _mode, Program& p){
	bool value = (_mode == TEXT) ? true : false;
	p.main_tbox->engage(value);
	p.rack_view->engage(!value);
	p.mode = _mode;
	p.mode_switched = true;
	p.rack_view->refresh();
}



void handle_universal_input(sf::Event& event, Program& p){
	// User clicked the windows close button
	if (event.type == sf::Event::Closed){
		p.running = false;
		return;

	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Space:
			if (LSHIFT_IS_DOWN){ // silence any sounding alarms
				Alarm::silence();
				p.univ_triggered = true;
			}
			break;

		case sf::Keyboard::Escape: // back out / end program
			if (!p.editing && p.mode != QUIT){
				p.mode = QUIT;
				auto quit_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
															"Would you like to save current rack ("+p.rack->name+")?");
				p.draw_list.push_back(quit_popup);
				p.univ_triggered = true;
			}
			break;
		}
	}
}


void handle_quit_mode(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Y:
			p.prepare_quit(true);
			break;

		case sf::Keyboard::N:
			p.prepare_quit(false);
			break;

		case sf::Keyboard::Escape:
			p.draw_list.pop_back();
			//p.mode = TEXT; // TODO: Have it revert to whatever the previous mode was.
			switch_mode(TEXT, p);
			break;
		}
	}
}


void handle_rack_mode(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::J: // move rack selector down
			if (LSHIFT_IS_DOWN){
				p.rack->set_select(p.rack->size()-1);
				p.rack_view->refresh();
			} else {
				p.rack->select_move(jb::DOWN);
				//p.rack_view->select_move(jb::DOWN);
				p.rack_view->refresh();
			}
			break;

		case sf::Keyboard::K: // move rack selector up
			if (LSHIFT_IS_DOWN){
				p.rack->set_select(0);
				p.rack_view->refresh();
			} else {
				p.rack->select_move(jb::UP);
				p.rack_view->refresh();
			}
			break;

		case sf::Keyboard::Enter: // duplicate currently selected alarm
			p.rack->duplicate_alarm();
			p.rack_view->refresh();
			break;

		case sf::Keyboard::Backspace: // remove alarm from rack
			p.rack->remove_alarm();
			if (p.rack->size() == 0){
				switch_mode(TEXT, p);
			}
			p.rack_view->refresh();
			break;

		case sf::Keyboard::T: // toggle alarm active state
			p.rack->toggle_selection();
			p.rack_view->refresh();
			break;

		case sf::Keyboard::W: // increment duplicate time adjustment
			p.rack->adjust_dup_increment(5);
			break;

		case sf::Keyboard::S: // decrement duplicate time adjustment
			p.rack->adjust_dup_increment(-5);
			break;

		case sf::Keyboard::E: // edit alarm
			p.main_tbox->fill(p.rack->get_selection_message());
			switch_mode(TEXT, p);
			p.editing = true;
			break;

		case sf::Keyboard::Tab: // switch modes
			switch_mode(TEXT, p);
			break;
		}
	}
}



void handle_text_mode(sf::Event& event, Program& p){
	// for text events
	if (event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			p.main_tbox->write(event.text.unicode);
		}

		// for special key events
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Tab: // switch modes
			if (!p.editing && p.rack->size() != 0){
				switch_mode(RACK, p);
			}
			break;

		case sf::Keyboard::Backspace: // remove char
			if (LSHIFT_IS_DOWN){
				p.main_tbox->clear_back(true);
			} else {
				p.main_tbox->delete_char();
			}
			break;

		case sf::Keyboard::Return: // submit buffer to new/edited alarm
			if (p.editing == false){
				p.rack->add_alarm(p.main_tbox->get_buffer());
			} else {
				p.rack->edit_selection(p.main_tbox->get_buffer());
				p.editing = false;
			}
			p.main_tbox->clear_all();
			switch_mode(RACK, p);
			break;

		case sf::Keyboard::Left: // move cursor back
			if (LSHIFT_IS_DOWN){
				p.main_tbox->shift_cursor(jb::TOP);
			} else {
				p.main_tbox->shift_cursor(jb::UP);
			}
			break;

		case sf::Keyboard::Right: // move cursor forward
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				p.main_tbox->shift_cursor(jb::BOTTOM);
			} else {
				p.main_tbox->shift_cursor(jb::DOWN);
			}
			break;

		case sf::Keyboard::Escape: // cancel edit
			p.editing = false;
			p.main_tbox->clear_all();
			switch_mode(RACK, p);
		}
	}
}


