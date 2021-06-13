#pragma once
#include <SFML/Window.hpp>

#include <jb.hpp>
#include <Alarm.hpp>


enum Mode {
	TEXT = 0,
	RACK
};


struct Program; // FD


struct InputManager {

	Program* p;


	InputManager(){}
	InputManager(Program *_p);
	void handle_universal_input(sf::Event& event);
	void handle_rack_mode(sf::Event& event);
	void handle_text_mode(sf::Event& event);
	void switch_mode(Mode _mode);
	
};


