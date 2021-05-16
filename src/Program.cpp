#include <Program.hpp>
#include <string.h>


bool Program::running 				= true;
Window Program::window 				= Window(500, 500); // create the window
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


	//sf::Clock clock;
	// run the program as long as the window is open
	while (window->isOpen()) {

		// check all the windows events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed){
				end(); return;

			// keyboard input
			} else if (event.type == sf::Event::KeyPressed){

				if (event.key.code == sf::Keyboard::Escape){
					end(); return;
				}
				else if (event.key.code == sf::Keyboard::J){
					// move selection downwards
					rack->select_move(jb::DOWN);
					currentMenu->update();
				}
				else if (event.key.code == sf::Keyboard::K){
					// move selection upwards
					rack->select_move(jb::UP);
					currentMenu->update();
				}
				else if (event.key.code == sf::Keyboard::Enter){
					rack->duplicate_alarm();
					currentMenu->update();
				}
				else if (event.key.code == sf::Keyboard::O){
					rack->toggle_selection();
					currentMenu->update();
				}
				else if (event.key.code == sf::Keyboard::Space){
					rack->quiet();
				}
			}
			

			//float dt = clock.restart().asSeconds();

			window->clear(sf::Color(228,240,238,255)); // clear and set bg color

			window->draw(*(currentMenu));

			window->display();

		}
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



