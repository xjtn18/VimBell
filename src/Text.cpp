#include <Text.hpp>

Text::Text(vb::Transform _tf, std::string _content, sf::Font& _font, int _fontsize)
	: Entity(_tf)
{
	txt = sf::Text(_content, _font, _fontsize);
	sf::FloatRect bounds = txt.getLocalBounds();

	max_bounds = sf::Text(")", _font, _fontsize).getLocalBounds();

	tf.w = bounds.width + bounds.left;
	tf.h = max_bounds.height;

	set_color(VB_WHITE);
}


void Text::set_color(sf::Color c){
	txt.setFillColor(c);
}

void Text::set_text(const std::string& new_text){
	txt.setString(new_text);
}

void Text::center_xaxis(){
	sf::FloatRect bounds = txt.getLocalBounds();
	txt.setOrigin((int)(bounds.width/2 + bounds.left), (int) max_bounds.top);
}

void Text::center_yaxis(){
	sf::FloatRect bounds = txt.getLocalBounds();
	txt.setOrigin(0, (int) max_bounds.height/2 + max_bounds.top - 1);
}

void Text::update(float dt){
	txt.setPosition(tf.x, tf.y);
}


void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(txt);
}

