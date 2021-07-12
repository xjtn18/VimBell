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
			auto quit_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
														"Save current rack ("+p.rack->name+")?");
			quit_popup->yes_routine = [&](){
				p.prepare_quit(true);
			};
			quit_popup->no_routine = [&](){
				p.prepare_quit(false);
			};

			p.draw_list.push_back(quit_popup);
			p.univ_triggered = true;

			p.engage_with(quit_popup);
			break;
		}
	}
}






