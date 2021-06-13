#pragma once
#include <SFML/Graphics.hpp>

#include <AlarmCell.hpp>
#include <Debug.hpp>
#include <Rack.hpp>
#include <jb.hpp>
#include <Entity.hpp>

#include <vector>
#include <initializer_list>



class Menu : public Entity {
	//
	// A vertical arrangment of buttons.
	//
	std::vector<AlarmCell> buttons;		// vector of menu elements
	int padding;					// x,y location of menu; padding distance between menu elements
	std::shared_ptr<Rack> rack_state;
	bool engaged;

public:

	Menu(){}

	Menu(jb::Transform _tf, int _padding, std::shared_ptr<Rack> _rack_state, bool _engaged = false)
		: Entity(_tf), padding(_padding), rack_state(_rack_state), engaged(_engaged)
	{ }
	

	void update(){
		// call this function whenever the menu layout changes
		buttons.clear();
		int _y = tf.y; // temp y position
		const std::vector<Alarm> alarms = rack_state->get_alarms();

		for (int i = 0; i < alarms.size(); ++i){ // set each button location
			std::string info;

			if (alarms[i].is_active()){
				info = (std::string) alarms[i].get_target() + "     " + alarms[i].get_msg();
			} else {
				info = (std::string) alarms[i].get_target() + "  X  " + alarms[i].get_msg();
			}
			AlarmCell button(tf.w, 60, info);

			button.set_xy(tf.x, _y); // all buttons have the same x coordinate
			if (engaged && i == rack_state->get_select_index()){
				button.select();
			}
			buttons.push_back(button);
			_y += button.get_height() + padding; // next button position
		}
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const AlarmCell& button : buttons){ // draw each button
			target.draw(button);
		}
	}


	void set_button_color(sf::Color c){
		for (AlarmCell& button : buttons){
			button.set_color(c);
		}
	}

	inline void engage(bool value){
		engaged = value;
	}
	
};



