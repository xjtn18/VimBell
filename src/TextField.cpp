#include <TextField.hpp>
#include <Program.hpp>


auto blink_func = [] (float x) -> float { return pow(-pow(sin(x - 0.6f), 18) + 1, 80); };


auto TextField::field_speaker = new aud::Speaker(100.0f, false);


void TextField::cleanup(){
	delete field_speaker;
}


TextField::TextField(const char* init_buffer, jb::Transform _tf, bool _engaged)
	: Entity(_tf),
	  box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h))),
	  cursor(TextCursor({tf.x + 24, tf.y, 19, tf.h-10})),
	  line(Line(init_buffer, cursor.get_width()*2, _tf, 24, cursor.get_width(), sf::Color(50,50,50))),
	  engaged(_engaged)
{
#define CURSOR_HOME {tf.x + 24, tf.y, tf.w, tf.h}
	bufmax = tf.w / cursor.get_width() - 2;
	box.setOrigin(0, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(JB_RED);

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


void TextField::shift_cursor(jb::Direc direction){
	switch(direction){
	case jb::TOP:
		cursor.set_pos(0, CURSOR_HOME);
		line.index = 0;
		break;

	case jb::BOTTOM:
		if (line.line.size() > 0){
			cursor.set_pos(line.line.size(), CURSOR_HOME);
			line.index = line.line.size();
		}
		break;

   default: // remaining directions
	   line.index += direction;
		if (!jb::clamp(line.index, 0, line.line.size()+1)){
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
	std::string result;
	for (int i = 0; i < line.line.size(); ++i){
		result += line.line[i].getString();
	}
	return result;
}


void TextField::update(float dt){
	if (engaged){
		float inc = 0.05 * dt;
		lerp += inc;
		if (lerp > 360) lerp = 0;
		cursor.lerp = lerp;
		cursor.update(dt);
		line.update(dt, lerp);
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



void TextField::handler(sf::Event& event, Program& p){
	// for text events
	if (event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			p.main_tbox->write(event.text.unicode);
		}

		// for special key events
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Tab: // switch modes
			if (!p.editing && p.rack->size() != 0){
				p.engage_with((Entity**)&(p.rack_view));
			}
			break;

		case sf::Keyboard::Backspace: // remove char
			if (LSHIFT_IS_DOWN){
				p.main_tbox->clear_back(true);
			} else {
				p.main_tbox->delete_char();
			}
			break;

		case sf::Keyboard::Return: // submit text to new/edited alarm
			if (p.editing == false){
				p.rack->add_alarm(p.main_tbox->get_buffer());
			} else {
				p.rack->edit_selection(p.main_tbox->get_buffer());
				p.editing = false;
			}
			p.main_tbox->clear_all();
			p.engage_with((Entity**)&(p.rack_view));
			break;

		case sf::Keyboard::Left: // move cursor back
			if (LSHIFT_IS_DOWN){
				p.main_tbox->shift_cursor(jb::TOP);
			} else {
				p.main_tbox->shift_cursor(jb::UP);
			}
			break;

		case sf::Keyboard::Right: // move cursor forward
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				p.main_tbox->shift_cursor(jb::BOTTOM);
			} else {
				p.main_tbox->shift_cursor(jb::DOWN);
			}
			break;

		case sf::Keyboard::Escape: // cancel edit
			p.editing = false;
			p.main_tbox->clear_all();
			p.engage_with((Entity**)&(p.rack_view));
		}
	}
}
