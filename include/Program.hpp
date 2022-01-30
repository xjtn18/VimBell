#pragma once
#include <SFML/System.hpp>
#include <functional>
#include <cmath>

#include <vb.hpp>
#include <Animation.hpp>


// FD's
struct Entity;
struct VStack;
struct HStack;
struct LineShape;
struct BorderedRect;
struct TextField;
struct DigitalTimeView;
struct Menu;
struct Rack;
struct Chooser;
struct Image;


enum Stage {
	RACKSELECT,
	RACKOPEN
};


struct Program {
	bool running = true,
		saving = false;

	// window
	sf::RenderWindow *window_ptr;


	// UI entities
	// Main
	TextField *main_tbox = nullptr;
	DigitalTimeView *main_digitime = nullptr;
	Menu *rack_view = nullptr;
	VStack *section_stack = nullptr;
	Image *bg_clock = nullptr;
	sf::Text fps;
	Entity *engaged_entity = nullptr;
	Entity *last_engaged = nullptr;

	// Rack Select
	Chooser *rack_chooser = nullptr;


	// program state
	std::vector<Entity*> draw_list;
	std::shared_ptr<Rack> rack;
	Stage stage;


	// sectors
	int padding;
	BorderedRect *sector_top, *bezel_top, *bezel_bottom;


	Program();
	void stop();
	void quit();
	void cleanup();
	void set_pane_rack_chooser();
	void set_pane_main();
	void engage_with(Entity *ent);
	void update_frame(float dt);
	void draw_frame(sf::RenderWindow& window);
	void mainloop();

};


