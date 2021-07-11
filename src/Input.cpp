#include <Input.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>



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
															"Save current rack ("+p.rack->name+")?");
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
			//switch_mode(TEXT, p);
			p.engage_with((Entity**)&(p.main_tbox));
			break;
		}
	}
}






