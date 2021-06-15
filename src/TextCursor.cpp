#include <TextCursor.hpp>


TextCursor::TextCursor(jb::Transform _tf)
	:  tf(_tf), box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h)))
{
	blink_lerp 		= 0.0f;
	blink_target 	= 255.0f;
	blink_rate 		= 0.05f;
	box.setOrigin(tf.w/2, tf.h/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(50,50,50));
}


TextCursor::~TextCursor(){
}


void TextCursor::translate(const int new_x, const int new_y){
	// first 2 lines may not be necessary
	tf.x += new_x;
	tf.y += new_y;
	box.setPosition(tf.x, tf.y);
}


void TextCursor::reset_blink_state(){
	blink_lerp = 0.0f;
}


void TextCursor::update(float dt){
	float inc = blink_rate * dt;
	blink_lerp += inc;
	if (blink_lerp >= blink_target) blink_lerp = 0;

	float x = 180/PI * blink_lerp;
	auto blink_func = [=] (float x) -> float { return pow(-pow(sin(x - 0.6f), 18) + 1, 60); };
	
	sf::Color color = box.getFillColor();
	color.a = blink_target * blink_func(x);
	box.setFillColor(color);
}



void TextCursor::move(int dir){
	translate(dir * tf.w, 0);
	reset_blink_state();
}


void TextCursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
}


