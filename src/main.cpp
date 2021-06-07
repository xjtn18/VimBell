#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <Window.hpp>
#include <Debug.hpp>
#include <Speaker.hpp>
#include <Menu.hpp>
#include <TextField.hpp>
#include <DigitalTimeView.hpp>
#include <Image.hpp>
#include <Rack.hpp>
#include <SaveLoad.hpp>


#define PI 3.14159265



enum Mode {
	TEXT = 0,
	RACK
};


namespace prog {
	// window setup
	Window main_window					= Window(750, 750); // create the window
	const int WINW					      = main_window.get_width();
	const int WINH					      = main_window.get_height();

	// dynamic bools
	bool running							= true,
		univ_triggered						= false,
		editing								= false,
		mode_switched						= false;

	// UI entities
	auto main_tbox							= TextField("", {(int)(225), 75, (int)(500), 50}, true);
	auto main_digitime					= DigitalTimeView({50, 75, 0, 0});
	Menu* rack_view						= nullptr;

	// program state
	std::shared_ptr<Rack> rack			= nullptr;
	Mode mode								= TEXT; // initial mode is text mode

	// sectors
	int padding = 1;
	sf::RectangleShape sector_top    ({(float)WINW-padding*2, 120});
	sf::RectangleShape bezel_top     ({(float)WINW-padding*2, 30});
	sf::RectangleShape bezel_bottom  ({(float)WINW-padding*2, 30});
}

using namespace prog;


std::ostream& operator<<(std::ostream& os, const sf::FloatRect& rect){
	os << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << std::endl;
	return os;
}



void program_cleanup(){
	// free all remaining program heap memory and audio buffers
	Alarm::cleanup();
	Rack::cleanup();
	aud::cleanup();

	rack.reset();			// delete current rack
	delete rack_view;		// delete current menu
}


void quit(){
	//
	// Clean heap memory and close the program window
	//

	save_rack(rack);
	program_cleanup();
	main_window.get_window().close(); // close window
}


void switch_mode(Mode _mode){
	bool value = (_mode == TEXT) ? true : false;
	main_tbox.engage(value);
	rack_view->engage(!value);
	mode = _mode;
	mode_switched = true;
}


void handle_universal_input(sf::Event& event){
	// User clicked the windows close button
	if (event.type == sf::Event::Closed){
		running = false;
		return;

	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){
		case sf::Keyboard::Space:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				Alarm::silence();
				univ_triggered = true;
			}
			break;
		case sf::Keyboard::Escape:
			running = false;
		}
	}
}


void handle_rack_mode(sf::Event& event){
	if (event.type == sf::Event::KeyPressed){

		switch (event.key.code){
		case sf::Keyboard::J:
			rack->select_move(jb::DOWN);
			break;

		case sf::Keyboard::K:
			rack->select_move(jb::UP);
			break;

		case sf::Keyboard::Enter:
			rack->duplicate_alarm();
			break;

		case sf::Keyboard::Backspace:
			rack->remove_alarm();
			if (rack->size() == 0){
				switch_mode(TEXT);
			}
			break;

		case sf::Keyboard::O:
			rack->toggle_selection();
			break;

		case sf::Keyboard::W:
			rack->adjust_dup_increment(5);
			break;

		case sf::Keyboard::S:
			rack->adjust_dup_increment(-5);
			break;

		case sf::Keyboard::E:
			main_tbox.fill(rack->get_selection_message());
			switch_mode(TEXT);
			editing = true;
			break;
		}

		if (event.key.code == sf::Keyboard::Tab){
			switch_mode(TEXT);
		}
	}
}



void handle_text_mode(sf::Event& event){
	// for text events
	if (event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			main_tbox.write(event.text.unicode);
		}

		// for special key events
	} else if (event.type == sf::Event::KeyPressed){

		switch (event.key.code){
		case sf::Keyboard::Tab:
			if (!editing && rack->size() != 0){
				switch_mode(RACK);
			}
			break;

		case sf::Keyboard::Backspace:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				main_tbox.clear_buffer();
			} else {
				main_tbox.delete_char();
			}
			break;

		case sf::Keyboard::Return:
			if (editing == false){
				rack->add_alarm(main_tbox.get_buffer());
				//rack_view->anim_create();
			} else {
				rack->edit_selection(main_tbox.get_buffer());
				editing = false;
			}
			main_tbox.clear_buffer();
			switch_mode(RACK);
			break;
		}
	}
}



void setup_sectors(){
	sector_top.setOrigin(-padding,-padding-1);
	sector_top.setFillColor(sf::Color(50,50,50));
	sector_top.setOutlineColor(sf::Color(150,150,150));
	sector_top.setOutlineThickness(padding);

	bezel_top.setOrigin(-padding,-padding-1);
	bezel_top.setFillColor(sf::Color(50,50,50));
	bezel_top.setOutlineColor(sf::Color(150,150,150));
	bezel_top.setOutlineThickness(padding);

	bezel_bottom.setOrigin(-padding,-padding-1);
	bezel_bottom.setFillColor(sf::Color(50,50,50));
	bezel_bottom.setOutlineColor(sf::Color(150,150,150));
	bezel_bottom.setOutlineThickness(padding);
	bezel_bottom.setPosition(0, WINH - (bezel_bottom.getSize().y+3));
}


void update_UI_entities(float dt){
	// update UI entities
	main_tbox.update(dt);
	main_digitime.update(dt);
	rack_view->update(); // TODO: Try to optimize (only call when needed), since it is hefty operation.
}


void draw_frame(sf::RenderWindow& window){
	// draw objects to frame TODO: Make an array of UI elements and call draw on each one.
	window.draw(*(rack_view));
	window.draw(sector_top);
	window.draw(main_digitime);
	window.draw(main_tbox);

	window.draw(bezel_top);
	window.draw(bezel_bottom);
}



void mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = main_window.get_window();
	window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);

	sf::Clock clock;


	while (running && window.isOpen()) {
		window.clear(sf::Color(20,20,20,20)); // clear last frame and set bg color

		sf::Event event;
		univ_triggered = false;
		mode_switched = false;
		while (window.pollEvent(event)) {

			handle_universal_input(event); // handle universal commands regardless of whats engaged.
			if (univ_triggered) continue; // NOTE: Must be done this way, with a global boolean.
			if (mode == RACK){
				handle_rack_mode(event);
			} else if (!mode_switched && mode == TEXT){
				handle_text_mode(event);
			}
		}
		// all inputs polled for this frame


		update_UI_entities( clock.restart().asSeconds() );
		draw_frame(window);

		window.display(); // display final frame
	}
}





int main(int argc, char* argv[]){
	// Start the program

	char* exec_path = argv[0];
	// set root path
	jb::rootPath = jb::rtrim(exec_path, strlen(exec_path), '/'); // does not work, returns only relative path

	// setup any static members
	AlarmCell::setup();
	TextField::setup();
	aud::load_all(); // load all the UI sounds

	setup_sectors();
	load_rack(rack); // load saved alarm rack

	rack_view = new Menu({WINW/2, (int)sector_top.getSize().y + padding*3, WINW, 0}, 1, rack);

	// run main program loop
	mainloop();

	quit();
	return 0;
}



