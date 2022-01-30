#include <TextField.hpp>
#include <Program.hpp>
#include <Menu.hpp>
#include <Rack.hpp>
#include <DigitalTimeView.hpp>
#include <Speaker.hpp>
#include <AlarmCell.hpp>
#include <sstream>
#include <iomanip>


auto blink_func = [] (float x) -> float { return pow(-pow(sin(x - 0.6f), 18) + 1, 80); };


auto TextField::field_speaker = new aud::Speaker(100.0f, false);


void TextField::cleanup(){
	delete field_speaker;
}


TextField::TextField(vb::Transform _tf, const char* init_content, bool _engaged)
	: Entity(_tf, _engaged),
	  box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h))),
	  cursor(TextCursor({tf.x + 24, tf.y, 19, tf.h-10})),
	  line(Line(_tf, init_content, cursor.get_width()*2 - 6, 24, cursor.get_width(), sf::Color(50,50,50)))
{
	CURSOR_HOME = {tf.x + 24, tf.y, 0, 0};
	bufmax = tf.w / cursor.get_width() - 2;
	box.setOrigin(0, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(100,100,100));
	box.setOutlineThickness(1);
	box.setOutlineColor(sf::Color(50,50,50));

	cursor.lerpf = blink_func;
	line.lerpf = blink_func;
}


TextField::~TextField(){
}


void TextField::reset(){
	lerp = 0;
}


void TextField::write(const char character){
	// write a char to the text field
	if (line.line.size() < bufmax){
		line.insert_char(character);
		cursor.move(1);
	}
	reset();
}


void TextField::delete_char(){
	// delete char preceding the cursor in text field
	if (line.index > 0){
		line.remove_char();
		cursor.move(-1);
	} else {
		field_speaker->play("error.wav");
	}
	reset();
}


void TextField::shift_cursor(vb::Direc direction){
	switch(direction){
	case vb::TOP:
		cursor.set_pos(0, CURSOR_HOME);
		line.index = 0;
		break;

	case vb::BOTTOM:
		if (line.line.size() > 0){
			cursor.set_pos(line.line.size(), CURSOR_HOME);
			line.index = line.line.size();
		}
		break;

   default: // other directions
	   line.index += direction;
		if (!vb::clamp(line.index, 0, line.line.size()+1)){
			cursor.move(direction);
		}
	}
	reset();
}


void TextField::engage(bool value){
	engaged = value;
	if (value){
		reset();
	}
	line.engage(value);
}


void TextField::clear_back(bool audible){
	if (audible && line.index == 0){
	  field_speaker->play("error.wav");
	}
	cursor.set_pos(0, CURSOR_HOME);
	line.clear_back();
	reset();
}


void TextField::clear_all(){
	cursor.set_pos(0, CURSOR_HOME);
	line.clear_all();
	reset();
}




std::string TextField::get_buffer() const {
	return vb::trim(line.get_string());
}


void TextField::update(float dt){
	if (engaged){
		float inc = 0.08 * dt;
		if (insertmode) lerp += inc; // only render blink in insert mode
		if (lerp > 360) lerp = 0;

		cursor.lerp = lerp;
		line.lerp = lerp;
		cursor.update(dt);
		line.update(dt);
	}
}


void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	if (engaged){
		target.draw(cursor);
	}
	target.draw(line);
}


void TextField::fill(std::string content){
	line.set(content.c_str());
	cursor.set_pos(line.index, CURSOR_HOME);
	reset();
}


void TextField::center_xaxis(){
	box.setOrigin(tf.w/2, 0);
	sf::FloatRect fr = box.getGlobalBounds();
	cursor.tf.x = fr.left + 24;
}

void TextField::center_yaxis(){
	box.setOrigin(0, tf.h/2);
	sf::FloatRect fr = box.getGlobalBounds();
	cursor.tf.y = fr.top/2;
}


bool TextField::handler(sf::Event& event, Program& p){
	// for text events
	if (insertmode == true && event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			write(event.text.unicode);
			return true;
		}

		// for command events
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::I:
			if (insertmode) return false;
			insertmode = true;
			return true;

		case sf::Keyboard::Tab: // engage other entity
			if (!p.rack_view->editing) {
				if (p.rack->size() != 0){
					insertmode = false;
					p.engage_with(p.rack_view);
				}
				return true;
			}
			return false;


		case sf::Keyboard::Backspace: // remove char
			if (insertmode){
				if (LSHIFT_IS_DOWN){
					clear_back(true);
				} else {
					delete_char();
				}
			}
			return true;


		case sf::Keyboard::Return: // submit text to new/edited alarm
			insertmode = false;
			p.rack_view->add(p);
			return true;


		case sf::Keyboard::H: // move cursor back
			if (insertmode) return false;
			if (line.index == 0){
				p.engage_with(p.main_digitime);
			} else if (LSHIFT_IS_DOWN){
				shift_cursor(vb::TOP);
			} else {
				shift_cursor(vb::UP);
			}
			return true;

		case sf::Keyboard::L: // move cursor forward
			if (insertmode) return false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				shift_cursor(vb::BOTTOM);
			} else {
				shift_cursor(vb::DOWN);
			}
			return true;

		case sf::Keyboard::J: // move cursor forward
			if (insertmode) return false;
			if (!p.rack_view->editing && p.rack->size() > 0) p.engage_with(p.rack_view);
			return true;

		case sf::Keyboard::Escape: // cancel edit
			cursor.lerp = 0;
			line.lerp = 0;
			cursor.update(0.0);
			line.update(0.0);
			this->reset();
			if (p.rack_view->editing && !insertmode){
				p.rack_view->editing = false;
				clear_all();
				p.engage_with(p.rack_view);
				return true;
			} else if (insertmode){
				insertmode = false;
				return true;
			}
		}
	}
	return false;
}


