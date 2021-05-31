#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <Window.hpp>
#include <Debug.hpp>
#include <Speaker.hpp>
#include <Menu.hpp>
#include <TextField.hpp>
#include <Image.hpp>
#include <Rack.hpp>

#include <cajun/json/reader.h>
#include <cajun/json/writer.h>
#include <cajun/json/elements.h>
#include <fstream>


#define PI 3.14159265


enum Mode {
	TEXT = 0,
	RACK
};


namespace prog {
	bool running 							= true;
	bool universal_triggered 			= false;
	Mode mode 								= TEXT; // initial mode is text mode
	Window main_window 					= Window(750, 750); // create the window
	const int WIN_WIDTH					= main_window.get_width();
	const int WIN_HEIGHT					= main_window.get_height();
	auto main_tbox 						= TextField("", {(int)WIN_WIDTH/2, 75, WIN_WIDTH - 100, 50}, true);
	std::shared_ptr<Rack> rack 		= nullptr;
	Menu* current_menu 					= nullptr;
}

using namespace prog;


void load_rack(){
	using namespace json;
	rack = std::shared_ptr<Rack>(new Rack);

	std::fstream fs;
	fs.open("R1.rack", std::fstream::in); // TODO: give racks a name, and save it to a file
																// with that same name.
   Object objDocument;
   //const Object& objRoot = objDocument;
	try {
		Reader::Read(objDocument, fs);
	} catch (Reader::ScanException& e){
		fs.close();
		return; // nothing to load
	}
	fs.close();

	const Array& arrayAlarms = objDocument["Workday"];
   Array::const_iterator it(arrayAlarms.Begin()), itEnd(arrayAlarms.End());
   for (; it != itEnd; ++it){ // for each Alarm
		const Object& objAlarm = *it;

		// get the alarm target time
		const Number& hour = objAlarm["TargetHour"];
		const Number& minute = objAlarm["TargetMinute"];
		jb::Time t = {(int) hour.Value(), (int) minute.Value()};

		// get the alarm message
		const String& objMessage = objAlarm["Message"];
		std::string msg = objMessage.Value();

		// get the active state
		const Boolean& objActive = objAlarm["Active"];
		bool active = objActive.Value();
		rack->insert_alarm(Alarm(t, msg, active));
		// TODO: we probably dont want the select index to be at the end when loading a rack at start
	}

}


void save_rack(){
	using namespace json;

   Array arrayAlarms;
	std::vector<Alarm> alarms = rack->get_alarms();

	for (auto& a : alarms){
		Object objAPA;
		objAPA["Message"] = String(a.get_msg());
		objAPA["TargetHour"] = Number(a.get_target().hour);
		objAPA["TargetMinute"] = Number(a.get_target().minute);
		objAPA["Active"] = Boolean(a.is_active());
		arrayAlarms.Insert(objAPA);
	}

   Object objDocument;
   objDocument["Workday"] = arrayAlarms;

	std::fstream fs;
	fs.open("R1.rack", std::fstream::out); // TODO: give racks a name, and save it to a file
																// with that same name.
	Writer::Write(objDocument, fs);
	fs.close();
}



// TODO: try calling cleanup AFTER the main event loop is returned from (in int main)
void program_cleanup(){
	// free all remaining program heap memory and audio buffers
	Alarm::cleanup();
	Rack::cleanup();
	aud::cleanup();

	rack.reset(); 			// delete current rack
	delete current_menu; 	// delete current menu
}


void end(){
	//
	// Clean heap memory and close the program window
	//

	//std::my_thread::sleep_for(std::chrono::milliseconds(100));
	save_rack();
	program_cleanup();
	main_window.get_window()->close(); // close window
}


void switch_mode(Mode _mode){
	bool value = (_mode == TEXT) ? true : false;
	main_tbox.engage(value);
	current_menu->engage(!value);
	mode = _mode;
}


void handle_universal_input(sf::Event& event){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){
			case sf::Keyboard::Space:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					Alarm::silence();
					universal_triggered = true;
				}
				break;

			case sf::Keyboard::Escape:
				end();
				running = false;
				return;

		}
	}
}


void handle_alarm_mode(sf::Event& event){
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
				if (rack->size() != 0){
					switch_mode(RACK);
				} // else error sound?
				break;

			case sf::Keyboard::Backspace:
				main_tbox.delete_char();
				break;

			case sf::Keyboard::Return:
				rack->add_alarm(main_tbox.get_buffer());
				main_tbox.clear_buffer();
				switch_mode(RACK);
				break;

		}
	}
}



void mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow* window = main_window.get_window();
	window->setFramerateLimit(120);
	//window->setVerticalSyncEnabled(true);


	sf::Clock clock;

	while (running && window->isOpen()) {
		window->clear(sf::Color(5,5,5,5)); // clear last frame and set bg color

		sf::Event event;
		universal_triggered = false;
		while (window->pollEvent(event)) {
			
			// User clicked the windows close button
			if (event.type == sf::Event::Closed){
				end();
				return;
			}

			handle_universal_input(event); // handle universal commands regardless of whats engaged.
			if (!running) return; 			// we could have ended the program
			if (universal_triggered) continue;

			if (mode == RACK){ // RACK MODE
				handle_alarm_mode(event);

			} else if (mode == TEXT){ // TEXT MODE
				handle_text_mode(event);
			}
		}
		// all inputs polled for this frame


		float dt = clock.restart().asSeconds();

		// update program objects
		main_tbox.update(dt);
		current_menu->update(); // TODO: Try to optimize (only call when needed), since it is hefty operation.

		// draw objects to frame
		window->draw(*(current_menu));
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


	// setup any static members
	AlarmCell::setup();
	TextField::setup();
	aud::load_all(); // load all the UI sounds

	load_rack();
	current_menu = new Menu({WIN_WIDTH/2, 200, WIN_WIDTH, WIN_HEIGHT}, 1, rack);

	// run main program loop
	mainloop();

	return 0;
}



