#include <DigitalTimeView.hpp>
#include <Program.hpp>
#include <Speaker.hpp>
#include <Menu.hpp>
#include <Rack.hpp>
#include <TextField.hpp>
#include <AlarmCell.hpp>
#include <sstream>
#include <iomanip>


using namespace vb;


aud::Speaker *DigitalTimeView::clock_speaker = new Speaker(100.0f, false);

void DigitalTimeView::cleanup(){
	delete clock_speaker;
}


void set_origin_center(sf::CircleShape& circle){
	// sets the origin of the shape to its local center
	sf::Vector2f origin(0,0);
	for (int i = 0; i < circle.getPointCount()-1; ++i){
		origin += circle.getPoint(i);
	}
	circle.setOrigin(origin/(float)circle.getPointCount());
}



DigitalTimeView::DigitalTimeView(vb::Transform _tf)
	: Entity(_tf),
	  line(Line(_tf, "12:00", 50, 0, 30, VB_WHITE)),
	  top_arrow(8, 3),
	  bottom_arrow(8, 3),
	  index(1),
	  meridiem(ANTE),
	  lerp(0),
	  lerp_target(5)
{
	// position the selector arrows
	float x_pos = (line.line[index + (2*index)].getPosition().x + line.line[index + (2*index) + 1].getPosition().x) / 2;
	top_arrow.setPosition(x_pos, tf.y - 35);
	top_arrow.setFillColor(VB_GREEN);
	set_origin_center(top_arrow);

	bottom_arrow.setPosition(x_pos, tf.y + 31);
	bottom_arrow.setFillColor(VB_GREEN);
	bottom_arrow.setRotation(180);
	set_origin_center(bottom_arrow);


	uint8_t grayout = 25;
	sf::FloatRect bounds;

	sf::Vector2f optsize(100,50);
	selector = sf::RectangleShape(optsize);
	selector.setOrigin(optsize.x/2, optsize.y/2);
	selector.setPosition(WINW-(optsize.x+optsize.x/2+20), WINH-75);
	selector.setFillColor(VB_GREEN);

	sf::Vector2f lt = selector.getPosition();
	sf::Vector2f rt = selector.getPosition() + sf::Vector2f(100,0);


	libmono.loadFromFile("res/fonts/FONT_LIBMONO.ttf");

	txt_AM = sf::Text("AM", libmono, 40);
	txt_AM.setFillColor(sf::Color(255,255,255,255));
	bounds = txt_AM.getGlobalBounds();
	txt_AM.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
	txt_AM.setPosition(lt);
	//round_position(&txt_AM);
	round_origin(&txt_AM);

	txt_PM = sf::Text("PM", libmono, 40);
	txt_PM.setFillColor(sf::Color(255,255,255,grayout));
	bounds = txt_PM.getGlobalBounds();
	txt_PM.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
	txt_PM.setPosition(rt);
	//round_position(&txt_PM);
	round_origin(&txt_PM);


	anim = PositionAnimation(&selector, lt, rt);
	anim.rate = 3.0;
	anim.f 			= [](float x) { return pow(-pow(1/(x/2 + 0.5) - 1, 3) + 1, 3); }; // fluid transition
	anim.inversef 	= [](float x) { return 2/((cbrt(cbrt(-x) + 1)) + 1) - 1; }; // its inverse

	// this function describes how the animation will modulate certain objects
	anim.stepper = [&](float y) -> void {
		float not_y = 1-y;
		uint8_t full = 255;
		uint8_t grayout = 25;

		if (anim.forw) std::swap(y, not_y);

		set_fill_alpha(txt_AM, get_intermediate_int(full, grayout, not_y));
		set_fill_alpha(txt_PM, get_intermediate_int(full, grayout, y));

		if (anim.forw) std::swap(y, not_y);
	};
}


void DigitalTimeView::alter_digit(int direction){
	std::string time_strs = line.get_string();

	if (index == 0){ // modifying hour
		int new_hour = std::stoi(time_strs.substr(0, 2)) + direction;
		std::string new_hour_str = (new_hour >= 10) ? 
			std::to_string(new_hour) : "0" + std::to_string(new_hour);
		if (!vb::clamp(new_hour, 1, 13)){
			line.line[index].setString(new_hour_str[0]);
			line.line[index+1].setString(new_hour_str[1]);
		} else {
			if (direction == -1){
				line.line[index].setString("1");
				line.line[index+1].setString("2");
			} else {
				line.line[index].setString("0");
				line.line[index+1].setString("1");
			}
		}

	} else if (index == 1){ // modifying minute
		int new_minute = std::stoi(time_strs.substr(3, 2)) + direction;
		std::string new_minute_str = (new_minute >= 10) ? 
			std::to_string(new_minute) : "0" + std::to_string(new_minute);
		if (!vb::clamp(new_minute, 0, 60)){
			// + 2 and + 3 to properly map index 1 to values in the line
			line.line[index+2].setString(new_minute_str[0]);
			line.line[index+3].setString(new_minute_str[1]);
		} else {
			if (direction == -1){
				line.line[index+2].setString("5");
				line.line[index+3].setString("9");
			} else {
				line.line[index+2].setString("0");
				line.line[index+3].setString("0");
			}
		}
	}
}


void DigitalTimeView::move_selector(int direction){
	index += direction;
	if (!vb::clamp(index, 0, 2)){
		// move selection arrows
		float x_pos = (line.line[index + (2*index)].getPosition().x + line.line[index + (2*index) + 1].getPosition().x) / 2;
		top_arrow.setPosition(x_pos, top_arrow.getPosition().y);
		bottom_arrow.setPosition(x_pos, bottom_arrow.getPosition().y);
	}

}


void DigitalTimeView::switch_meridiem(){
	if (anim.forw) anim.back();
	else anim.forward();
	meridiem = (Meridiem)((meridiem+1) % 2);
}


vb::Time DigitalTimeView::get_time(){
	// returns military time
	vb::Time time(line.get_string());
	if (meridiem == POST){
		time = (time.hour != 12) ? time + 12 * 60 : time; // add 12 hours for PM, unless it is 12 PM
	} else { // meridiem is ANTE
		time = (time.hour != 12) ? time : time + 12 * 60; // keep AM the same, unless it is 12 AM
	}
	return time;
}


void DigitalTimeView::engage(bool value){
	engaged = value;
}


void DigitalTimeView::update(float dt){
	float rate = 0.1;
	int target = 255;
	float inc = rate * dt;
	lerp += inc;
	if (lerp >= lerp_target) lerp = 0;
	float clr = cos(180/PI * lerp) + 1;
	
	
	sf::Color last = line.line[2].getFillColor();
	last.a = target/2 * clr;
	line.line[2].setFillColor(last);

	anim.step(dt); // meridiem selection display
}


void DigitalTimeView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(line);
	target.draw(selector);
	target.draw(txt_AM);
	target.draw(txt_PM);
	if (engaged){
		target.draw(top_arrow);
		target.draw(bottom_arrow);
	}
}



bool DigitalTimeView::handler(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::K:
			if (LSHIFT_IS_DOWN){
				alter_digit(5);
			} else {
				alter_digit(1);
			}
			return true;

		case sf::Keyboard::J:
			if (LSHIFT_IS_DOWN){
				alter_digit(-5);
			} else {
				alter_digit(-1);
			}
			return true;

		case sf::Keyboard::L:
			{
				int last_index = index;
				move_selector(1);
				if (index == last_index && index == 1) p.engage_with(p.main_tbox);
			}
			return true;

		case sf::Keyboard::H:
			move_selector(-1);
			return true;

		case sf::Keyboard::M:
			switch_meridiem();
			return true;

		case sf::Keyboard::Return: // submit text to new/edited alarm
			p.rack_view->add(p);
			return true;

		case sf::Keyboard::Tab:
			if (!p.rack_view->editing) p.engage_with(p.rack_view);
			return true;
		}
	}
	return false;
}



