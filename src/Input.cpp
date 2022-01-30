#include <Input.hpp>
#include <Program.hpp>
#include <YesNoPopup.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>
#include <SaveLoad.hpp>
#include <Menu.hpp>


void handle_global_input(sf::Event& event, Program& p){
	// User clicked the windows close button
	if (event.type == sf::Event::Closed){
		p.stop();
		return;

	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Space:
			if (LALT_IS_DOWN){ // silence any sounding alarms
				Alarm::silence();
				p.rack_view->set_all_idle();
			}
			break;


		case sf::Keyboard::Escape: // back out / end program
			{
				switch (p.stage){
				case RACKOPEN:
					{
						auto quit_popup = new YesNoPopup({WINW/2, WINH/2, 0, 0},
																	"Save current rack ("+vb::trimmable(p.rack->name, 11)+")?");
						quit_popup->yes_routine = [&](){
							save_rack(p.rack);
							Alarm::silence();
							p.set_pane_rack_chooser();
						};

						quit_popup->no_routine = [&](){
							Alarm::silence();
							p.set_pane_rack_chooser();
						};

						p.draw_list.push_back(quit_popup);

						p.engage_with(quit_popup);
					}
					break;

				case RACKSELECT:
					p.stop();
					break;
				}
			}
			break;
		}
	}
}






