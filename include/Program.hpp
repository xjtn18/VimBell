#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <Window.hpp>
#include <Menu.hpp>
#include <TextField.hpp>
#include <DigitalTimeView.hpp>
#include <Rack.hpp>
#include <BorderedRect.hpp>
#include <Debug.hpp>
#include <SaveLoad.hpp>
#include <VStack.hpp>
#include <InputManager.hpp>



struct Program {
	bool running							= true,
		  univ_triggered					= false,
		  editing								= false,
		  mode_switched						= false;

	// window setup
	const int WINW = 750;
	const int WINH = 750;
	Window main_window = Window(WINW, WINH); // create the window

	// UI entities
	TextField main_tbox;
	DigitalTimeView main_digitime;
	Menu *rack_view;

	// program state
	std::shared_ptr<Rack> rack;
	Mode mode;
	InputManager IM;

	// sectors
	int padding;
	BorderedRect* sector_top;
	sf::RectangleShape bezel_top, bezel_bottom;

	Program();
	void ask_yes_no(std::string question, std::function<void(void)> yes_callback);
	bool ask_yes_no(std::string question);
	void quit();
	void setup_bezels();
	void update_frame(float dt);
	void draw_frame(sf::RenderWindow& window);
	void mainloop();
	void cleanup();
};

