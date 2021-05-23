#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <Window.hpp>
#include <Debug.hpp>
#include <Sound.hpp>
#include <Menu.hpp>
#include <TextField.hpp>
#include <Image.hpp>
#include <Rack.hpp>



#define PI 3.14159265

enum Mode {
	TEXT = 0,
	ALARM
};



bool running 							= true;
Window main_window 					= Window(500, 750); // create the window
const unsigned int WIN_WIDTH		= main_window.get_width();
const unsigned int WIN_HEIGHT		= main_window.get_height();

std::shared_ptr<Rack> rack 	= nullptr;
Menu* currentMenu 				= nullptr;
Mode mode 							= TEXT; // initial mode is text mode
TextField main_tbox("", {(int)WIN_WIDTH/2, 50, 400, 50}, true);



void cleanup(){
	// free all remaining program heap memory and device objects (audio etc)

	Sound::cleanup();
	Alarm::cleanup();
	rack.reset(); 			// delete current rack
	delete currentMenu; 	// delete current menu
}


void end(){
	//
	// Clean heap memory and close the program window
	//

	sf::sleep(sf::milliseconds(100));
	cleanup();
	main_window.get_window()->close(); // close window
}



void handle_alarm_mode(sf::Event& event){
	switch (event.key.code){
		case sf::Keyboard::Escape:
			end();
			running = false;
			return;

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
			break;

		case sf::Keyboard::O:
			rack->toggle_selection();
			break;

		case sf::Keyboard::Space:
			rack->quiet();
			break;
	}
}



void event_loop(){
	//
	// Main program loop
	//

	sf::RenderWindow* window = main_window.get_window();
	window->setFramerateLimit(120);
	//window->setVerticalSyncEnabled(true);


	sf::Clock clock;

	while (running && window->isOpen()) {
		window->clear(sf::Color(228,240,238,255)); // clear and set bg color

		sf::Event event;
		while (window->pollEvent(event)) {
			
			// USER CLICKED WINDOW CLOSE
			if (event.type == sf::Event::Closed){
				end();
				return;
			}

			// ALARM MODE
			if (mode == ALARM){
				if (event.type == sf::Event::KeyPressed){
					handle_alarm_mode(event);
					if (!running) return;

					if (event.key.code == sf::Keyboard::Tab){
						main_tbox.set_active(true);
						mode = TEXT;
					}
				}

			// TEXT MODE
			} else if (mode == TEXT){
				// for text events
				if (event.type == sf::Event::TextEntered){
					if (event.text.unicode >= 32 && event.text.unicode <= 126){
						main_tbox.write(event.text.unicode);
					}

				// for special key events
				} else if (event.type == sf::Event::KeyPressed){
					if (event.key.code == sf::Keyboard::Tab){
						main_tbox.set_active(false);
						mode = ALARM;

					} else if (event.key.code == sf::Keyboard::Backspace){
						main_tbox.delete_char();

					} else if (event.key.code == sf::Keyboard::Return){
						rack->add_alarm(main_tbox.get_buffer());
						main_tbox.clear_buffer();
						main_tbox.set_active(false);
						mode = ALARM;

					} else if (event.key.code == sf::Keyboard::Escape){
						end();
						return;
					}
				}
			}
		}

		float dt = clock.restart().asSeconds();

		// update program objects
		main_tbox.update(dt);
		currentMenu->update(); // @TODO: Try to optimize (only call when needed), since it is hefty operation.

		// draw object to frame
		window->draw(*(currentMenu));
		window->draw(main_tbox);

		window->display(); // display final frame
	}
}





int main(int argc, char* argv[]){
	//
	// Start the program
	//

	char* exec_path = argv[0];
	// set root path
	jb::rootPath = jb::rtrim(exec_path, strlen(exec_path), '/'); // does not work, returns only relative path

	// create Rack (will load from file in future)
	rack = std::shared_ptr<Rack>(new Rack);

	// setup any static members
	Button::SETUP();

	// create current Menu
	currentMenu = new Menu(WIN_WIDTH, WIN_HEIGHT, 1, WIN_WIDTH/2, WIN_HEIGHT/3, rack);

	// run main program event loop
	event_loop();

	return 0;
}



