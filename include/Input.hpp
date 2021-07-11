#pragma once

#include <jb.hpp>
#include <Alarm.hpp>


enum Mode {
	TEXT = 0,
	RACK,
	QUIT
};


struct Program; // FD

void handle_universal_input(sf::Event& event, Program& p);
void handle_quit_mode(sf::Event& event, Program& p);
	

