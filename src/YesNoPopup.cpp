#include <YesNoPopup.hpp>
#include <Program.hpp>
#include <Text.hpp>


YesNoPopup::YesNoPopup(vb::Transform _tf, const std::string& _question)
	: Entity(_tf)
{
	float padding = 100;

	// dimmer
	dimmer = sf::RectangleShape({(float) WINW, (float) WINH});
	dimmer.setFillColor(sf::Color(30,30,30,200));

	sf::FloatRect bounds;

	// question text
	question = sf::Text(_question, FONT_LIBMONO_B, 30);
	question.setFillColor(VB_WHITE);
	bounds = question.getGlobalBounds();
	question.setOrigin((int)(bounds.width/2), (int)(30 * .75 - 2));
	question.setPosition((int)tf.x, (int)tf.y - (bounds.height));

	// box
	box.setSize({bounds.width + padding/2, bounds.height + padding});
	sf::Vector2f size = box.getSize();
	box.setOrigin(size.x/2, size.y/2);
	box.setPosition(tf.x, tf.y);
	box.setFillColor(sf::Color(50,50,50));
	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color(100,100,100));

	// yes + no
	option_yes = new Text({0,0,0,0}, "yes (y)", FONT_LIBMONO, 25);
	option_yes->set_color(VB_GREEN);

	option_no = new Text({0,0,0,0}, "no (n)", FONT_LIBMONO, 25);
	option_no->set_color(VB_RED);

	int answer_padding = 50;
	answers = HStack ({tf.x - option_yes->tf.w - answer_padding/2, tf.y, 0, 0}, answer_padding, {option_yes, option_no});

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


bool YesNoPopup::handler(sf::Event& event, Program& p){
	if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Y:
			yes_routine();
			return true;

		case sf::Keyboard::Enter:
			yes_routine();
			return true;

		case sf::Keyboard::N:
			no_routine();
			return true;

		case sf::Keyboard::Escape:
			p.engage_with(p.last_engaged);
			p.draw_list.pop_back(); // @NOTE: popup should always come last, but this feels error prone.
											// Need way of specifying which entity specificially to destroy.
			return true;
		}
	}
	return false;
}


