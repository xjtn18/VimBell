#include <Program.hpp>
#include <string.h>


bool Program::running = true;
ThreadClock* Program::tClock = nullptr;

WindowWrapper Program::windowWrapper = WindowWrapper(500, 500); // create the window
Menu* Program::currentMenu = &mainMenu;


//
// Menus
//
Menu Program::mainMenu = Menu(1, Program::windowWrapper.getWindowWidth()/2, Program::windowWrapper.getWindowHeight()/2, {
	Button(300, 60, "start", [](){
			dlog("start pressed");
	}),

	Button(300, 60, "options", [](){
			Program::changeMenu(&(Program::optionsMenu));
	}),

	Button(300, 60, "exit", [](){
			Program::stop();
	})
});


Menu Program::optionsMenu = Menu(1, Program::windowWrapper.getWindowWidth()/2, Program::windowWrapper.getWindowHeight()/2, {
	Button(300, 60, "option 1", [](){
			dlog("option 1");
	}),

	Button(300, 60, "option 2", [](){
			dlog("option 2");
	}),

	Button(300, 60, "option 3", [](){
			dlog("option 3");
	}),

	Button(300, 60, "<", [](){
			Program::changeMenu(&(Program::mainMenu));
	})
});



//
// Change what menu is displayed
// 
void Program::changeMenu(Menu* newMenu){
	Program::currentMenu = newMenu;
}


//
// Stop the program
// 
void Program::stop(){
	sf::sleep(sf::milliseconds(200));
	Program::cleanup();
	Program::windowWrapper.getWindow()->close();
}


void Program::cleanup(){
	Program::tClock->stop();
	delete tClock;

	// call sub-cleanups
	Button::cleanup();
	Rack::cleanup();
}



//
// Main program loop
// 
void Program::eventLoop(){

	sf::RenderWindow* window = Program::windowWrapper.getWindow();
	//int winw = Program::windowWrapper.getWindowWidth();
	//int winh = Program::windowWrapper.getWindowHeight();
	window->setFramerateLimit(120);
	window->setVerticalSyncEnabled(true);


	//aud::Sound music_MainMenu("res/music_MainMenu.wav", 20, true);
	//music_MainMenu.play();

	
	//sf::Clock clock;
	// run the program as long as the window is open
	while (window->isOpen()) {

		// check all the windows events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed){
				Program::stop();

			// keyboard input
			} else if (event.type == sf::Event::KeyPressed){

				if (event.key.code == sf::Keyboard::Escape){
					Program::stop();
				}
				
			// mouse input
			} else if (event.type == sf::Event::MouseButtonPressed){

				if (event.mouseButton.button == sf::Mouse::Button::Left){
					Program::currentMenu->checkPress(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (window->hasFocus()){
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				Program::currentMenu->checkHover(mousePos.x, mousePos.y);
			}


			//float dt = clock.restart().asSeconds();

			window->clear(sf::Color(228,240,238,255)); // clear and set bg color

			window->draw(*(Program::currentMenu));
			window->display();

		}
	}
}




//
// Start the program
//
void Program::init(char* execPath){
	jb::rootPath = jb::rtrim(execPath, strlen(execPath), '/'); // does not work, returns only relative path
	Rack::currentRack = std::shared_ptr<Rack>(new Rack);
	Rack::currentRack->add_alarm();
	Program::tClock = new ThreadClock(Rack::currentRack);
	Program::eventLoop();
}



