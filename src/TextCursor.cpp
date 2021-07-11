#include <TextCursor.hpp>


TextCursor::TextCursor(jb::Transform _tf)
	:  Entity(_tf), box(sf::RectangleShape(sf::Vector2f(tf.w, tf.h)))
{
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



void TextCursor::update(float dt){
	float x = 180/PI * lerp;
	sf::Color color = box.getFillColor();
	color.a = blink_target * lerpf(x);
	box.setFillColor(color);
}



void TextCursor::move(int dir){
	translate(dir * tf.w, 0);
}


void TextCursor::set_pos(int index, jb::Transform plane_ref){
	tf.x = plane_ref.x + tf.w * index;
	tf.y = plane_ref.y;
	box.setPosition(tf.x, tf.y);
}


void TextCursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
}


