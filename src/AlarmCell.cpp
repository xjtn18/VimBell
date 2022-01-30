#include <AlarmCell.hpp>
#include <Text.hpp>
#include <cmath>


sf::Color AlarmCell::idleColor = sf::Color(80, 80, 80, 150);
sf::Color AlarmCell::hoverColor = sf::Color(132, 231, 47, 150);
sf::Color AlarmCell::hoverTriggered = sf::Color(230, 130, 112);



AlarmCell::AlarmCell(vb::Transform _tf, const std::string _text, int _stacc, int _interval)
	: Entity(_tf),
	  text(_text)
{
	box = sf::RectangleShape(sf::Vector2f(tf.w,tf.h));
	box.setFillColor(idleColor);

	bText = sf::Text(text, FONT_LIBMONO, (unsigned int) (tf.h/1.85));
	bText.setFillColor(VB_WHITE); // set font color
	sf::FloatRect textBounds = bText.getLocalBounds();
	bText.setOrigin(0, (int)(tf.h/2 - 3));

	stacc_indicator = new Text(vb::Transform::Zero, "x" + std::to_string(_stacc), FONT_LIBMONO, tf.h/1.85);
	stacc_indicator->center_yaxis();

	stacc_interval_indicator = new Text(vb::Transform::Zero, std::to_string(_interval), FONT_LIBMONO, tf.h/1.85);
	stacc_interval_indicator->center_yaxis();

	set_pos();
}



void AlarmCell::set_pos(){
	box.setPosition(tf.x, tf.y);
	bText.setPosition(tf.x + 25, tf.y + tf.h/1.8);

	stacc_indicator->tf.x = tf.w - 150;
	stacc_indicator->tf.y = tf.y + tf.h/2;
	stacc_indicator->update(0.0f);
	
	stacc_interval_indicator->tf.x = tf.w - 80;
	stacc_interval_indicator->tf.y = tf.y + tf.h/2;
	stacc_interval_indicator->update(0.0f);
};



void AlarmCell::set_color(sf::Color c){
	box.setFillColor(c);
}


void AlarmCell::engage(bool value){
	is_hovered = value;
	if (value == true) {
		if (!is_triggered) box.setFillColor(hoverColor);
		else box.setFillColor(hoverTriggered);
	} else {
		if (!is_triggered) box.setFillColor(idleColor);
		else box.setFillColor(VB_RED);
	}
}


void AlarmCell::idle(){
	box.setFillColor(idleColor);
	bText.setFillColor(VB_WHITE);
	stacc_indicator->set_color(VB_WHITE);
	stacc_interval_indicator->set_color(VB_WHITE);
	is_triggered = false;
}

void AlarmCell::idle_select(){
	box.setFillColor(hoverColor);
	bText.setFillColor(VB_WHITE);
	stacc_indicator->set_color(VB_WHITE);
	stacc_interval_indicator->set_color(VB_WHITE);
	is_triggered = false;
}


void AlarmCell::trigger(){
	box.setFillColor(VB_RED);
	bText.setFillColor(VBC_BG);
	stacc_indicator->set_color(VBC_BG);
	stacc_interval_indicator->set_color(VBC_BG);
	is_triggered = true;
}

void AlarmCell::trigger_select(){
	box.setFillColor(hoverTriggered);
	bText.setFillColor(VBC_BG);
	stacc_indicator->set_color(VBC_BG);
	stacc_interval_indicator->set_color(VBC_BG);
	is_triggered = true;
}


void AlarmCell::toggle(){
	if (active){
		sf::Color dim(80,80,80);
		box.setFillColor(hoverColor);
		bText.setFillColor(dim);
		stacc_indicator->set_color(dim);
		stacc_interval_indicator->set_color(dim);
		is_triggered = false;
	} else {
		this->idle_select();
	}
	active = !active;
}



void AlarmCell::update(float dt){
	set_pos();
}


void AlarmCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	target.draw(bText); // draw the button text
	target.draw(*stacc_indicator);
	target.draw(*stacc_interval_indicator);
}



