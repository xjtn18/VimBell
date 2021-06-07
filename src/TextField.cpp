#include <TextField.hpp>


sf::Font TextField::font;

void TextField::setup(){
	if (!TextField::font.loadFromFile("res/fonts/incon.ttf")){
		dlog("could not load font");
	}
}


TextField::TextField(const char* init_buffer, jb::Transform _tf, bool _engaged)
	: tf(_tf), box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h))),
	  cursor(TextCursor({tf.x + 24, tf.y, 19, tf.h-10})),
	  line(Line(init_buffer, cursor.get_width()*2, _tf, 24, cursor.get_width())),
	  engaged(_engaged)
{
	bufmax 			= tf.w / cursor.get_width() - 2;
	box.setOrigin(0, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(255, 101, 74));

}


TextField::~TextField(){
}


void TextField::write(const char character){
	// write a char to the text field
	if (line.index < bufmax){
		line.insert_char(character);
		cursor.move(1);
	}
}


void TextField::delete_char(){
	// delete preceding char in text field
	if (line.index > 0){
		line.remove_char();
		cursor.move(-1);
	}
}


void TextField::engage(bool value){
	if (value == true){
		cursor.reset_blink_state();
	}
	engaged = value;
}


void TextField::clear_buffer(){
	cursor.move(-line.index); // move cursor to front of field
	line.clear();
}


std::string TextField::get_buffer() const {
	std::string result;
	for (int i = 0; i < line.index; ++i){
		result += line.line[i].getString();
	}
	return result;
}


void TextField::update(float delta_time){
	cursor.update(delta_time);
}

void TextField::draw_buffer(sf::RenderTarget& target) const {
	for (auto& c : line.line){
		target.draw(c);
	}
}


void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	if (engaged){
		target.draw(cursor);
	}
	draw_buffer(target);
}


void TextField::fill(std::string content){
	clear_buffer();
	line.set(content.c_str());
	cursor.move(line.index); // move cursor to end of the field
}


