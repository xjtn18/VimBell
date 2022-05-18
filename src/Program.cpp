#include <Program.hpp>
#include <Entity.hpp>
#include <Text.hpp>
#include <Image.hpp>
#include <Speaker.hpp>
#include <SaveLoad.hpp>
#include <Stack.hpp>
#include <Shapes.hpp>
#include <Input.hpp>
#include <TextField.hpp>
#include <DigitalTimeView.hpp>
#include <Menu.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>
#include <AlarmCell.hpp>
#include <Option.hpp>
#include <Chooser.hpp>
#include <TextPrompt.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using namespace vb;



Program::Program()
{
	// setup any static members
	aud::load_all(); // load all the program sounds
	load_fonts();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	window_ptr = new sf::RenderWindow(sf::VideoMode(WINW, WINH), "VimBell", sf::Style::Titlebar | sf::Style::Close, settings);

	// Set the Icon
	sf::Image icon;
	icon.loadFromFile("res/images/clock-ico.png");
	window_ptr->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window_ptr->setFramerateLimit(60);

	// Load all UI entities at program start that can be created now,
	// regardless of whether or not they appear in the initial pane (draw_list).
	
	// UI entities
	main_digitime = new DigitalTimeView({30, 75, 0, 0});
	main_tbox = new TextField({180, 75, WINW - 180 - 25, 50}, "");

	// sectors
	sector_top = new BorderedRect({0, 0, WINW, 120}, 2);

	bezel_top = new BorderedRect({0, 0, WINW, 30}, 2);
	bezel_bottom = new BorderedRect({0, WINH-30, WINW, 30}, 2);

	sf::FloatRect bounds;

	// grid lines
	float grid_line_thickness = 2;
	auto yaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, grid_line_thickness, WINH});
	auto xaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, WINW, grid_line_thickness});

	bg_clock = new Image({WINW, WINH+150, 0, 0}, "res/images/roman_clock.png");
	float scale = 0.75;
	bg_clock->sprite.setScale(scale, scale);
	bg_clock->sprite.setColor(sf::Color(0,0,0,50));

	set_pane_rack_chooser();
}


void Program::set_pane_rack_chooser(){
	stage = RACKSELECT;

	rack_chooser = new Chooser({0, 0, WINW/3, 0}, 1);
	std::string filename;
	try {
		for (const auto& entry : fs::directory_iterator("racks/")){
			filename = entry.path().filename().stem().u8string();
			rack_chooser->options.push_back([=](){
				load_rack(*this, filename);
				set_pane_main();
			});
			// ^ must capture by value
			// The filename to pass to set_pane_main will be deleted upon exiting this function
			// unless we pass the filename by value to the lambda object.
			rack_chooser->insert(-1, new Option({0,0,WINW,50},filename));
		}
	} catch (std::filesystem::filesystem_error &ignored){ } // racks folder not found

	rack_chooser->options.push_back([&](){
			auto tp = new TextPrompt({CENTER_WIN_X-275, CENTER_WIN_Y-25, 550, 50}, "", true);
			tp->submit = [&](std::string rackname){
				rack = std::shared_ptr<Rack>(new Rack(rackname, *this)); // create new rack
				set_pane_main();
			};
			draw_list.push_back(tp);
			engage_with(tp);
		});
	rack_chooser->insert(-1, new Option({0,0,WINW,50},"+"));

	Text *title = new Text({CENTER_WIN_X,0,0,0}, "[create or load an alarm rack]", FONT_LIBMONO, 30);
	title->set_color(sf::Color(100,100,100));
	title->center_xaxis();
	VStack *v = new VStack({0,20,0,0}, 20, {
			title,
			rack_chooser
		});

	draw_list = { v };
	engage_with(rack_chooser);
}



void Program::set_pane_main(){
	stage = RACKOPEN;

	main_tbox->clear_all();
	rack_view = new Menu({0, 0, WINW, 0}, 1, rack);
	auto rack_name = new Text({CENTER_WIN_X, 0, 0, 0}, rack->name, FONT_LIBMONO, 20);
	rack_name->center_xaxis();
	rack_name->set_color(VB_WHITE);

	section_stack = new VStack(vb::Transform::Zero, 10, {
			sector_top,
			rack_name,
			rack_view
		});

	draw_list = {
		bg_clock,
		sector_top,
		section_stack,
		main_digitime,
		main_tbox,
		bezel_top,
		bezel_bottom
	};
	engage_with(main_tbox);
}


void Program::engage_with(Entity *ent){
	if (engaged_entity) engaged_entity->engage(false);
	last_engaged = engaged_entity;
	engaged_entity = ent;
	engaged_entity->engage(true);
}




void Program::cleanup(){
	// cleanup up audio resources
	Alarm::cleanup();
	Rack::cleanup();
	TextField::cleanup();
	DigitalTimeView::cleanup();
	aud::cleanup();

	rack.reset();			// delete current rack
	if (rack_view) delete rack_view;
	delete window_ptr;
}


void Program::stop(){
	running = false;
}



void Program::quit(){
	//
	// Close the program window and clean up heap
	//
	if (saving) save_rack(rack);
	window_ptr->close(); // close window
	cleanup();
}




void Program::update_frame(float dt){
	// update UI entities
	for (Entity *ent : draw_list){
	   ent->update(dt);
	}
}


void Program::draw_frame(sf::RenderWindow& window){
	for (sf::Drawable *ent : draw_list){
		window.draw(*ent);
	}
}



void Program::mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = *(window_ptr);
	sf::Clock clock;

	while (running && window.isOpen()) {
		window.clear(VBC_BG); // clear last frame and set bg color

		bool event_processed = false;
		sf::Event event;

		while (window.pollEvent(event)) {
			// @NOTE: A single character keystroke produces both a KeyPressed and a TextEntered event; be aware of that.
			// @NOTE: keystrokes shared by the current entity and the universals should prioritize the entity.
			// So entity handlers should be called first.
			
			// @FIXME: some events are processed by both the entity and the global handler.
			if (!event_processed)
				event_processed = engaged_entity->handler(event, *this);
			if (!event_processed)
				handle_global_input(event, *this);

		}
		// All inputs were polled for this frame.

		update_frame( clock.restart().asSeconds() );
		draw_frame(window);

		window.display(); // display completed frame

	}
}



