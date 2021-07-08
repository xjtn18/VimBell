#include <YesNoPopup.hpp>


YesNoPopup::YesNoPopup(jb::Transform _tf, const std::string& _question)
	: Entity(_tf)
{
	float padding = 100;

	// dimmer
	dimmer = sf::RectangleShape({(float) WINW, (float) WINH});
	dimmer.setFillColor(sf::Color(30,30,30,175));

	sf::FloatRect bounds;

	// question text
	question = sf::Text(_question, INCON_FONT, 30);
	bounds = question.getGlobalBounds();
	question.setOrigin(bounds.width/2, 30 * .75 - 2);
	question.setPosition(tf.x, tf.y - (bounds.height));

	// box
	box.setSize({bounds.width + padding/2, bounds.height + padding});
	sf::Vector2f size = box.getSize();
	box.setOrigin(size.x/2, size.y/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(60,100,140));
	box.setOutlineThickness(1);
	box.setOutlineColor(sf::Color::White);

	// yes + no

	option_yes = new Text({0,0,0,0}, "yes (y)", INCON_FONT, 30);
	//option_yes.setOrigin(bounds.width/2, 30 * .75 - 2);

	option_no = new Text({0,0,0,0}, "no (y)", INCON_FONT, 30);
	//option_no.setOrigin(bounds.width/2, 30 * .75 - 2);

	answers = HStack ({tf.x, tf.y, 0, 0}, 50, {option_yes, option_no});

}


void YesNoPopup::update(float dt){
	answers.update(dt);
}


void YesNoPopup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(dimmer);
	target.draw(box);
	target.draw(question);
	target.draw(answers);
}
