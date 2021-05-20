#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Window.hpp>
#include <Debug.hpp>
#include <Sound.hpp>
#include <Menu.hpp>
#include <TextField.hpp>
#include <Image.hpp>
#include <Rack.hpp>
#include <cmath>


#define PI 3.14159265


class Program {

public:
	// main window
	static bool running;
	static Window window;
	static Menu* currentMenu;
	static std::shared_ptr<Rack> rack;


	static void init(char* execPath);
	static void event_loop();
	static void cleanup();
	static void end();

};


