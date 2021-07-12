#pragma once
#include <SFML/System.hpp>
#include <functional>
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
		univ_triggered	= false;

	// window setup
	sf::RenderWindow *window_ptr;

	// UI entities
	TextField *main_tbox;
	DigitalTimeView *main_digitime;
	Menu *rack_view;
	VStack *section_stack;
	sf::Text fps;

	// program state
	std::vector<Entity*> draw_list;
	std::shared_ptr<Rack> rack;
	Entity *engaged_entity = nullptr;
	Entity *last_engaged = nullptr;

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
	void engage_with(Entity *ent);

};

