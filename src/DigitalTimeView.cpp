#include <DigitalTimeView.hpp>


sf::Font DigitalTimeView::font;



DigitalTimeView::DigitalTimeView(jb::Transform _tf)
	: tf(_tf),
	  line(Line("", 50, _tf, 0, 30)),
	  lerp(0),
	  lerp_target(5)
{
   DigitalTimeView::font.loadFromFile("res/fonts/incon.ttf");

	sf::Color digit_color = sf::Color::White;
	int y = tf.y;
	int wid = 25;
	for (int i = 0; i < 5; ++i){
		if (i != 2){
			line.insert_char('7');
		} else {
			line.insert_char(':');
		}
		line.line.back().setFillColor(digit_color); // set font color
	}

}


void DigitalTimeView::update(float dt){
	return;
	float rate = 0.1;
	int target = 255;
	float inc = rate * dt;
	lerp += inc;
	if (lerp >= lerp_target) lerp = 0;
	float clr = cos(180/PI * lerp) + 1;
	
	
	sf::Color last = line.line[2].getFillColor();
	last.a = target/2 * clr;
	line.line[2].setFillColor(last);

}

void DigitalTimeView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& c : line.line){
		target.draw(c);
	}
}
