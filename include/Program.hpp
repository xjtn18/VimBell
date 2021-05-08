#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <WindowWrapper.hpp>
#include <Debug.hpp>
#include <Sound.hpp>
#include <Button.hpp>
#include <Menu.hpp>
#include <Image.hpp>
#include <Rack.hpp>
#include <ThreadClock.hpp>
#include <cmath>


#define PI 3.14159265


class Program {

public:
	// main window
	static bool running;
	static WindowWrapper windowWrapper;
	static Menu mainMenu, optionsMenu;
	static Menu* currentMenu;


	static void init(char* execPath);
	static void stop();
	static void eventLoop();
	static void changeMenu(Menu* newMenu);
	static void cleanup();

protected:
	 static ThreadClock* tClock;
};


