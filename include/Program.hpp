#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <Menu.hpp>
#include <TextField.hpp>
#include <DigitalTimeView.hpp>
#include <Rack.hpp>
#include <BorderedRect.hpp>
#include <Debug.hpp>
#include <SaveLoad.hpp>
#include <Stack.hpp>
#include <Input.hpp>



struct Program {
	bool running = true,
		saving = false,
		univ_triggered	= false,
		editing = false,
		mode_switched = false;

	// window setup
	sf::RenderWindow *window_ptr;

	// UI entities
	TextField *main_tbox;
	DigitalTimeView *main_digitime;
	Menu *rack_view;
	VStack *v;
	sf::Text fps;

	// program state
	std::vector<Entity*> draw_list;
	std::shared_ptr<Rack> rack;
	Mode mode;

	// sectors
	int padding;
	BorderedRect *sector_top, *bezel_top, *bezel_bottom;

	Program();
	void prepare_quit(bool _saving);
	void quit();
	void update_frame(float dt);
	void draw_frame(sf::RenderWindow& window);
	void mainloop();
	void cleanup();
	void test_input();
};

