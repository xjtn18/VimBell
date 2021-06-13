#include <Program.hpp>



Program::Program()
	: IM(this)
{
	// window setup

	// UI entities
	main_tbox = TextField("", {225, 75, 500, 50}, true);
	main_digitime = DigitalTimeView({50, 75, 0, 0});

	load_rack(rack); // load saved alarm rack
	rack_view = new Menu({WINW/2, 0, WINW, 0}, 1, rack);

	// program state
	mode = TEXT; // initial mode is text mode

	// sectors
	padding = 1;
	sector_top = new BorderedRect({0, 0, WINW, 120}, 5);

	bezel_top = sf::RectangleShape({(float)WINW-padding*2, 30});
	bezel_bottom = sf::RectangleShape({(float)WINW-padding*2, 30});
	setup_bezels();
}



void Program::ask_yes_no(std::string question, std::function<void(void)> yes_callback){
	std::string answer;
	while (std::cout << question << std::endl){
		std::cin >> answer;
		if (answer == "yes"){
			yes_callback();
			return;
		} else if (answer == "no"){
			return;
		} else {
			std::cout << "reply \"yes\" or \"no\"." << std::endl;
		}
	}
}

bool Program::ask_yes_no(std::string question){
	std::string answer;
	while (std::cout << question << std::endl){
		std::cin >> answer;
		if (answer == "yes"){
			return true;
		} else if (answer == "no"){
			return false;
		} else {
			std::cout << "reply \"yes\" or \"no\"." << std::endl;
		}
	}
	return false;
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
}




void Program::quit(){
	//
	// Clean heap memory and close the program window
	//
	auto save = [&](){save_rack(rack);};
	if (!DEV) ask_yes_no("Would you like to save the current rack (" + rack->get_name() + ")?", save);
	cleanup();
	main_window.get_window().close(); // close window
}




void Program::setup_bezels(){
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


void Program::update_frame(float dt){
	// update UI entities
	main_tbox.update(dt);
	main_digitime.update(dt);
	rack_view->update(); // TODO: Try to optimize (only call when needed), since it is hefty operation.
}


void Program::draw_frame(sf::RenderWindow& window){
	// draw objects to frame TODO: Make an array of UI elements and call draw on each one.
	window.draw(main_digitime);
	window.draw(main_tbox);

	window.draw(bezel_top);
	window.draw(bezel_bottom);
}



void Program::mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = main_window.get_window();
	window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);

	VStack v(WINW/2, 0, 0, {
			sector_top,
			rack_view
		});

	sf::Clock clock;


	while (running && window.isOpen()) {
		window.clear(sf::Color(20,20,20,20)); // clear last frame and set bg color

		sf::Event event;
		univ_triggered = false;
		mode_switched = false;

		while (window.pollEvent(event)) {

			IM.handle_universal_input(event); // handle universal commands regardless of whats engaged.
			if (univ_triggered) continue; // NOTE: Must be done this way, with a global boolean.
			if (mode == RACK){
				IM.handle_rack_mode(event);
			} else if (mode == TEXT && !mode_switched){
				IM.handle_text_mode(event);
			}
		}
		// all inputs polled for this frame

		update_frame( clock.restart().asSeconds() );
		window.draw(v);
		draw_frame(window);


		window.display(); // display final frame
	}
}



