#include <AlarmCell.hpp>

sf::Color AlarmCell::idleColor = sf::Color(80, 80, 80, 150);
sf::Color AlarmCell::hoverColor = sf::Color(132, 231, 47, 150);



AlarmCell::AlarmCell(jb::Transform _tf, const std::string _text)
	: Entity(_tf),
	  text(_text),
	  lerp(0)
{
	box = sf::RectangleShape(sf::Vector2f(tf.w,tf.h));
	box.setFillColor(idleColor);

	bText = sf::Text(text, FONT_LIBMONO, (unsigned int) (tf.h/1.85));
	bText.setFillColor(JB_WHITE); // set font color
	sf::FloatRect textBounds = bText.getLocalBounds();
	bText.setOrigin(0, (int)(tf.h/2 - 3));
	set_pos();
}




void AlarmCell::set_pos(){
	zone = sf::Rect<int>(tf.x-tf.w/2, tf.y-tf.h/2, tf.w, tf.h);
	box.setPosition(tf.x, tf.y);
	bText.setPosition(tf.x + 25, tf.y+tf.h/1.8);
};




void AlarmCell::set_color(sf::Color c){
	box.setFillColor(c);
}


void AlarmCell::engage(bool value){
	is_hovered = value;
	if (value) {
		box.setFillColor(hoverColor);
	} else {
		box.setFillColor(idleColor);
	}
}




void AlarmCell::update(float dt){
	if (is_hovered){
		lerp += (rate * dt);
		int rtarget = 89;
		int gtarget = 153;
		int btarget = 33;
		float x = 180/PI * lerp;
		if (x >= PI) lerp = 0;
		auto lerpf = [] (float x) -> float {return -(0.5 * (cos(x) + 1) - 1);};


		sf::Color last = box.getFillColor();
		last.r = (rtarget - hoverColor.r) * lerpf(x) + hoverColor.r;
		last.g = (gtarget - hoverColor.g) * lerpf(x) + hoverColor.g;
		last.b = (btarget - hoverColor.b) * lerpf(x) + hoverColor.b;
		box.setFillColor(last);

	}
	set_pos();
}


void AlarmCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	target.draw(bText); // draw the button text
	target.draw(stacc_indicator);
}



