#include <Text.hpp>

Text::Text(jb::Transform _tf, const char* _content, sf::Font& _font, int _fontsize)
	: Entity(_tf)
{
	txt = sf::Text(_content, _font, _fontsize);
	sf::FloatRect bounds = txt.getGlobalBounds();
	tf.w = bounds.width;
	tf.y = bounds.height;
}


void Text::update(float dt){
	txt.setPosition(tf.x, tf.y);
}


void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(txt);
}

