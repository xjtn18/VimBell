#pragma once
#include <SFML/Graphics.hpp>

#include <Button.hpp>
#include <Debug.hpp>
#include <Rack.hpp>
#include <jb.hpp>

#include <vector>
#include <initializer_list>



class Menu : public sf::Drawable {
	//
	// A vertical arrangment of buttons.
	//
	std::vector<Button> buttons;		// vector of menu elements
	int w, h, x, y, padding;					// x,y location of menu; padding distance between menu elements
	std::shared_ptr<Rack> rack_state;

public:

	Menu(){}

	Menu(int _w, int _h, int _padding, int _x, int _y, std::shared_ptr<Rack> _rack_state)
		: w(_w), h(_h), x(_x), y(_y), padding(_padding), rack_state(_rack_state)
		// @params:
		// 	padding: amount of space in pixels between each button
		// 	x and y: position of the menu
		// 	l: init list of Button objects
	{
		update();
	}
	

	void update(){
		// call this function whenever the menu is created or when menu layout changes
		buttons.clear();
		int _y = y; // temp button y
		const std::vector<Alarm> alarms = rack_state->get_alarms();

		for (int i = 0; i < alarms.size(); ++i){ // set each button location
			std::string info;

			if (alarms[i].is_active()){
				info = (std::string) alarms[i].get_target() + "     " + alarms[i].get_msg();
			} else {
				info = (std::string) alarms[i].get_target() + "  X  " + alarms[i].get_msg();
			}
			Button button(w, 60, info, [](){dlog("hi");});

			button.setXY(x, _y); // all buttons have the same x coordinate
			if (i == rack_state->get_select_index()){
				button.select();
			}
			buttons.push_back(button);
			_y += button.get_height() + padding; // next button position
		}
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const Button& button : buttons){ // draw each button
			target.draw(button);
		}
	}


	void set_button_color(sf::Color c){
		for (Button& button : buttons){
			button.set_color(c);
		}
	}


	void check_press(int mouseX, int mouseY){
		for (Button& button : buttons){
			button.check_press(mouseX, mouseY);
		}
	}


	void check_hover(int mouseX, int mouseY){
		for (Button& button : buttons){
			button.check_hover(mouseX, mouseY);
		}
	}
	
};



