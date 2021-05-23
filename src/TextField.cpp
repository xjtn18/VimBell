#include <TextField.hpp>



TextCursor::TextCursor(jb::Transform _tf)
	:  tf(_tf), box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h)))
{
	blink_lerp 		= 0.0f;
	blink_target 	= 10.0f;
	blink_rate 		= 20.0;
	show 				= true;
	box.setOrigin(tf.w/2, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color::Black);


}


int TextCursor::get_width() const {
	return tf.w;
}


void TextCursor::translate(const int new_x, const int new_y){
	// first 2 lines may not be necessary
	tf.x += new_x;
	tf.y += new_y;
	box.setPosition(tf.x, tf.y);
}


void TextCursor::reset_blink_state(){
	blink_lerp = 0.0f;
	if (!show){ // hidden
		show = true;
		blink_rate -= 10.0f;
	}
}


void TextCursor::update(float delta_time){
	blink_lerp += blink_rate * delta_time; // increment the blink_lerp by the blink_rate as a function -
													// of the frame delta time (framerate consistent).
	if (blink_lerp >= blink_target){
		blink_lerp = 0.0f; // reset blink_lerp to it stays within a simple range
		show = !show; // switch state of cursor (for blinking effect).
		if (show){ // slightly extend duration of the 'show' state of the blink.
			blink_rate -= 10.0f;
		} else {
			blink_rate += 10.0f;
		}
	}
}

TextCursor::~TextCursor(){
}


void TextCursor::move(int dir){
	translate(dir * tf.w, 0);
	reset_blink_state();
}


void TextCursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (show){
		target.draw(box); // draw the button box
	}
}




//////////////////////////////////////////
/////////////  TextField  ////////////////
//////////////////////////////////////////

sf::Font TextField::font;

TextField::TextField(const char* init_buffer, jb::Transform _tf, bool _active)
	: tf(_tf), box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h))), \
		cursor(TextCursor({tf.x - tf.w/2 + 24, tf.y, 18, tf.h-10})), active(_active)
{
	buffer_index 	= 0;
	bufmax 			= 20;
	buffer 			= (char*) calloc(bufmax, sizeof(char));

	strcpy(buffer, init_buffer);
	box.setOrigin(tf.w/2, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(231, 146, 71, 255));

	if (!TextField::font.loadFromFile("res/fonts/incon.ttf")){
		dlog("could not load font");
	}

	int cw = cursor.get_width();
	for (int i = 0; i < bufmax; ++i){
		tvec.push_back(sf::Text("", TextField::font, cursor.get_width()*2));
		tvec[i].setFillColor(sf::Color::Black); // set font color
		tvec[i].setPosition(tf.x - tf.w/2 + i*cw + 14, tf.y-22);
	}
	//sf::FloatRect font_bounds = get_font_local_bounds(TextField::font, 34);
	//text.setOrigin((int)font_bounds.width/2, (int)font_bounds.height/2);
	//text.setPosition(tf.x - tf.w/2 + 24, tf.y);
	// y j 

}


TextField::~TextField(){
	delete[] buffer;
}


void TextField::write(const char character){
	// write a char to the text field
	if (buffer_index < bufmax){
		buffer[buffer_index] = character;
		buffer_index += 1;
		cursor.move(1);
	}
}


void TextField::delete_char(){
	// delete preceding char in text field
	if (buffer_index > 0){
		buffer[buffer_index-1] = '\0';
		buffer_index -= 1;
		cursor.move(-1);
	}
}




void TextField::set_active(bool value){
	if (value == true){
		cursor.reset_blink_state();
	}
	active = value;
}


void TextField::clear_buffer(){
	cursor.move(-strlen(buffer)); // move cursor to front of field
	buffer_index = 0;
	for (int i = 0; i < bufmax; ++i){ // clean buffer
		buffer[i] = '\0';
	}
}


void TextField::update(float delta_time){
	cursor.update(delta_time);
	for (int i = 0; i < bufmax; ++i){
		tvec[i].setString(buffer[i]);
	}
}

void TextField::draw_buffer(sf::RenderTarget& target) const {
	for (const sf::Text& c : tvec){
		if (c.getString() != '\0'){
			target.draw(c);
		}
	}
}


void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	if (active){
		target.draw(cursor);
	}
	draw_buffer(target);
}


