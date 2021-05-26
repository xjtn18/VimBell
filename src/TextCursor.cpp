#include <TextCursor.hpp>


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


