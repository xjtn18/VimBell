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
#include <Chooser.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using namespace jb;



Program::Program()
{
	// setup any static members
	aud::load_all(); // load all the program sounds
	load_fonts();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	window_ptr = new sf::RenderWindow(sf::VideoMode(WINW, WINH), "jBell", sf::Style::Titlebar | sf::Style::Close, settings);

	// Set the Icon
   sf::Image icon;
   icon.loadFromFile(jb::get_image("clock-ico.png"));
   window_ptr->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window_ptr->setFramerateLimit(60);
	
	// UI entities
	main_digitime = new DigitalTimeView({30, 75, 0, 0});
	main_tbox = new TextField({180, 75, WINW - 180 - 25, 50}, "");

	// sectors
	sector_top = new BorderedRect({0, 0, WINW, 120}, 2);

	bezel_top = new BorderedRect({0, 0, WINW, 30}, 2);
	bezel_bottom = new BorderedRect({0, WINH-30, WINW, 30}, 2);

	sf::FloatRect bounds;

	/*
	// fps counter
	fps = sf::Text("0", FONT_LIBMONO, 30);
	bounds = fps.getLocalBounds();
	fps.setPosition(20, WINH - bounds.height - bounds.top - 5);
	fps.setFillColor(JB_GREEN);
	*/

	// grid lines
	float grid_line_thickness = 2;
	auto yaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, grid_line_thickness, WINH});
	auto xaxis = new LineShape({CENTER_WIN_X, CENTER_WIN_Y, WINW, grid_line_thickness});

	bg_clock = new Image({WINW, WINH, 0, 0}, "res/images/roman_clock.png");
	bg_clock->sprite.setScale(0.5, 0.5);
	bg_clock->sprite.setColor(sf::Color(0,0,0,50));


	rack_select = new Chooser({0, 0, WINW/3, 0}, 1);
	std::string filename;
	for (const auto& entry : fs::directory_iterator("racks/")){
		filename = entry.path().filename().stem();
		rack_select->options.push_back([&](){this->set_pane_main("my-alarms-1");});
		//rack_select->options.back()
	}

	set_pane_rack_select();
}


void Program::set_pane_rack_select(){
	draw_list = {
		rack_select
	};

	engage_with(rack_select);
}


void Program::set_pane_main(const std::string &filename){
	load_rack(rack, filename); // load saved alarm rack
	rack_view = new Menu({0, 0, WINW, 0}, 1, rack);

	auto rack_name = new Text({CENTER_WIN_X, 0, 0, 0}, rack->name, FONT_LIBMONO, 20);
	rack_name->center_xaxis();
	rack_name->set_color(JB_WHITE);

	section_stack = new VStack({0, 0, 0, 0}, 10, {
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
	if (engaged_entity){
		engaged_entity->engage(false); // disengage current entity
	}
	last_engaged = engaged_entity;
	engaged_entity = ent;
	engaged_entity->engage(true);
}


void Program::cleanup(){
	//std::this_thread::sleep_for(std::chrono::milliseconds(2000)); @NOTE for testing

	// cleanup up audio resources
	Alarm::cleanup();
	Rack::cleanup();
	TextField::cleanup();
	DigitalTimeView::cleanup();
	aud::cleanup();

	rack.reset();			// delete current rack
	delete rack_view;
	delete window_ptr;
}


void Program::prepare_quit(bool _saving){
	saving = _saving;
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
	
	// framerate
	/*
	static int count = 0;
	char c[6];
	sprintf(c, "%d", (int)(1/dt));
	if (count++ == 25){
		fps.setString(sf::String(std::string(c)));
		count = 0;
	}
	*/
}


void Program::draw_frame(sf::RenderWindow& window){
	for (sf::Drawable *ent : draw_list){
		window.draw(*ent);
	}

	//framerate
	//window.draw(fps);
}




void Program::mainloop(){
	//
	// Main program loop
	//

	sf::RenderWindow& window = *(window_ptr);
	sf::Clock clock;

	while (running && window.isOpen()) {
		window.clear(JBC_BG); // clear last frame and set bg color

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
		// all inputs polled for this frame

		update_frame( clock.restart().asSeconds() );
		draw_frame(window);


		window.display(); // display completed frame
	}
}



