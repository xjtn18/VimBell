#include <Program.hpp>
#include <string.h>


bool Program::running 				= true;
Window Program::window 				= Window(500, 750); // create the window
const unsigned int WIN_WIDTH		= Program::window.get_width();
const unsigned int WIN_HEIGHT		= Program::window.get_height();


std::shared_ptr<Rack> Program::rack 	= nullptr;
Menu* Program::currentMenu 				= nullptr;




void Program::end(){
	/*
	Stop the program
	*/

	sf::sleep(sf::milliseconds(200));
	Program::cleanup();
	Program::window.get_window()->close(); // close window
}


void Program::cleanup(){
	// free all remaining program heap memory and device objects (audio etc)

	Sound::cleanup();
	Alarm::cleanup();
	rack.reset(); 			// delete current rack
	delete currentMenu; 	// delete current menu
}



void Program::event_loop(){
	/*
	Main program loop
	*/

	sf::RenderWindow* window = Program::window.get_window();
	window->setFramerateLimit(120);
	window->setVerticalSyncEnabled(true);

	TextField my_text_field("", WIN_WIDTH/2, 50, 300, 50);

	//sf::Clock clock;
	// run the program as long as the window is open
	while (window->isOpen()) {

		window->clear(sf::Color(228,240,238,255)); // clear and set bg color

		// check all the windows events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed){
				end();
				return;

			// keyboard input
			} else if (event.type == sf::Event::KeyPressed){
				switch (event.key.code){

					case sf::Keyboard::Escape:
						end();
						return;

					case sf::Keyboard::J:
						rack->select_move(jb::DOWN);
						currentMenu->update();
						break;

					case sf::Keyboard::K:
						rack->select_move(jb::UP);
						currentMenu->update();
						break;

					case sf::Keyboard::Enter:
						rack->duplicate_alarm();
						currentMenu->update();
						break;

					case sf::Keyboard::Backspace:
						rack->remove_alarm();
						currentMenu->update();
						break;

					case sf::Keyboard::O:
						rack->toggle_selection();
						currentMenu->update();
						break;

					case sf::Keyboard::Space:
						rack->quiet();
						break;

					case sf::Keyboard::A:
						my_text_field.write();
						break;
				}
			}
			

			//float dt = clock.restart().asSeconds();




		}

		window->draw(*(currentMenu));
		window->draw(my_text_field);

		window->display();
	}
}




void Program::init(char* execPath){
	/*
	Start the program
	*/

	// set root path
	jb::rootPath = jb::rtrim(execPath, strlen(execPath), '/'); // does not work, returns only relative path

	// create Rack (will load from file in future)
	rack = std::shared_ptr<Rack>(new Rack);

	// setup any static members
	Button::SETUP();

	// create current Menu
	currentMenu = new Menu(WIN_WIDTH, WIN_HEIGHT, 1, WIN_WIDTH/2, WIN_HEIGHT/3, rack);

	// run main program event loop
	Program::event_loop();
}



