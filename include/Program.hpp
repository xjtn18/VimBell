#pragma once
#include <SFML/System.hpp>
#include <functional>
#include <cmath>

#include <jb.hpp>
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



struct Program {
	bool running = true,
		saving = false;

	// window
	sf::RenderWindow *window_ptr;


	// UI entities
	// Main
	TextField *main_tbox;
	DigitalTimeView *main_digitime;
	Menu *rack_view;
	VStack *section_stack;
	Image *bg_clock;
	sf::Text fps;
	Entity *engaged_entity = nullptr;
	Entity *last_engaged = nullptr;

	// Rack Select
	Chooser *rack_select;


	// program state
	std::vector<Entity*> draw_list;
	std::shared_ptr<Rack> rack;


	// sectors
	int padding;
	BorderedRect *sector_top, *bezel_top, *bezel_bottom;


	Program();
	void prepare_quit(bool _saving);
	void quit();
	void cleanup();
	void set_pane_rack_select();
	void set_pane_main(const std::string &filename);
	void engage_with(Entity *ent);
	void update_frame(float dt);
	void draw_frame(sf::RenderWindow& window);
	void mainloop();

};


