#include <Text.hpp>

Text::Text(jb::Transform _tf, std::string _content, sf::Font& _font, int _fontsize)
	: Entity(_tf)
{
	txt = sf::Text(_content, _font, _fontsize);
	sf::FloatRect bounds = txt.getLocalBounds();

	max_bounds = sf::Text(")", _font, _fontsize).getLocalBounds();

	tf.w = bounds.width + bounds.left;
	tf.h = max_bounds.height;
}

void Text::set_color(sf::Color c){
	txt.setFillColor(c);
}

void Text::center_xaxis(){
	sf::FloatRect bounds = txt.getLocalBounds();
	txt.setOrigin((int)(bounds.width/2 + bounds.left), (int) max_bounds.top);
}

void Text::center_yaxis(){
	sf::FloatRect bounds = txt.getLocalBounds();
	txt.setOrigin(0, (int) bounds.height + max_bounds.top);
}

void Text::update(float dt){
	txt.setPosition(tf.x, tf.y);
}


void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*
	auto bounds = txt.getGlobalBounds();
	sf::RectangleShape rec({bounds.width, bounds.height});
	rec.setPosition(bounds.left, bounds.top);
	rec.setFillColor(JB_GREEN);
	target.draw(rec);
	*/

	target.draw(txt);
}

