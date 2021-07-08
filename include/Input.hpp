#pragma once
#include <SFML/Window.hpp>

#include <jb.hpp>
#include <Alarm.hpp>


enum Mode {
	TEXT = 0,
	RACK,
	QUIT
};


struct Program; // FD


void switch_mode(Mode _mode, Program& p);
void handle_universal_input(sf::Event& event, Program& p);
void handle_quit_mode(sf::Event& event, Program& p);
void handle_rack_mode(sf::Event& event, Program& p);
void handle_text_mode(sf::Event& event, Program& p);
	

