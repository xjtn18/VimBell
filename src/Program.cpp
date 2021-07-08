#include <Program.hpp>



Program::Program()
{
	// setup any static members
	aud::load_all(); // load all the program sounds
	load_font();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	window_ptr = new sf::RenderWindow(sf::VideoMode(750, 750), "jBell", sf::Style::Titlebar | sf::Style::Close, settings);

	// Set the Icon
   sf::Image icon;
   icon.loadFromFile(jb::get_image("clock-ico.png"));
   window_ptr->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// UI entities
	main_tbox = new TextField("", {225, 75, 500, 50}, true);
	main_digitime = new DigitalTimeView({50, 75, 0, 0});

	load_rack(rack); // load saved alarm rack
	rack_view = new Menu({0, 0, WINW, 0}, 1, rack);

	// program state
	mode = TEXT; // initial mode is text mode

	// sectors
	padding = 1;
	sector_top = new BorderedRect({0, 0, WINW, 120}, 2);

	bezel_top = new BorderedRect({0, 0, WINW, 30}, 2);
	bezel_bottom = new BorderedRect({0, WINH-30, WINW, 30}, 2);

	// fps counter
	fps = sf::Text("0", INCON_FONT, 30);
	sf::FloatRect bounds = fps.getLocalBounds();
	fps.setPosition(20, WINH - bounds.height - bounds.top);
	fps.setFillColor(sf::Color::Green);

	v = new VStack({0, 0, 0, 0}, 0, {
			sector_top,
			rack_view
		});

	draw_list = {
		sector_top,
		v,
		main_digitime,
		main_tbox,
		bezel_top,
		bezel_bottom
	};


}





void Program::cleanup(){
	// free all remaining program heap memory and audio buffers
	//std::this_thread::sleep_for(std::chrono::milliseconds(2000)); @NOTE for testing purposes
	Alarm::cleanup();
	Rack::cleanup();
	TextField::cleanup();
	aud::cleanup();

	rack.reset();			// delete current rack
	delete rack_view;
	delete window_ptr;
}


void Program::prepare_quit(bool _saving){
	saving = _saving;
	running = false;
}



void Program::quit(){
	//
	// Clean heap memory and close the program window
	//
	if (saving) save_rack(rack);
	window_ptr->close(); // close window
	cleanup();
}




void Program::update_frame(float dt){
	// update UI entities
	for (Entity *ent : draw_list){
	   ent->update(dt);
	}

	// framerate
	static int count = 0;
	char c[6];
	sprintf(c, "%d", (int)(1/dt));
	if (count++ == 50){
		fps.setString(sf::String(std::string(c)));
		count = 0;
	}
}


void Program::draw_frame(sf::RenderWindow& window){
	for (sf::Drawable *ent : draw_list){
		window.draw(*ent);
	}

	//framerate
	window.draw(fps);

}




void Program::mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = *(window_ptr);
	window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);


	sf::Clock clock;

	while (running && window.isOpen()) {
		window.clear(sf::Color(20,20,20,20)); // clear last frame and set bg color

		univ_triggered = false;
		mode_switched = false;
		sf::Event event;

		while (window.pollEvent(event)) {
			handle_universal_input(event, *this); // handle universal commands regardless of whats engaged.
			if (univ_triggered) continue; // NOTE: Must be done this way, with a global boolean.
			if (mode == RACK){
				handle_rack_mode(event, *this);
			} else if (mode == TEXT && !mode_switched){
				handle_text_mode(event, *this);
			} else if (mode == QUIT){
				handle_quit_mode(event, *this);
			}
		}
		// all inputs polled for this frame

		update_frame( clock.restart().asSeconds() );
		draw_frame(window);


		window.display(); // display final frame
	}
}



