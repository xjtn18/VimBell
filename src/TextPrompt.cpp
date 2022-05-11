#include <TextPrompt.hpp>
#include <Program.hpp>
#include <Menu.hpp>
#include <Rack.hpp>
#include <DigitalTimeView.hpp>
#include <Speaker.hpp>
#include <AlarmCell.hpp>
#include <Chooser.hpp>


TextPrompt::TextPrompt(vb::Transform _tf, const char* init_content, bool _engaged)
	: TextField(_tf, init_content, _engaged)
{
	// dimmer
	dimmer = sf::RectangleShape({(float) WINW, (float) WINH});
	dimmer.setFillColor(sf::Color(30,30,30,200));
	insertmode = true;
}


void TextPrompt::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(dimmer);
	TextField::draw(target, states);
}

bool TextPrompt::handler(sf::Event& event, Program& p) {
	// for text events
	if (event.type == sf::Event::TextEntered){
		if (event.text.unicode >= 32 && event.text.unicode <= 126){
			write(event.text.unicode);
			return true;
		}

		// for special key events
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code){

		case sf::Keyboard::Backspace: // remove char
			if (LSHIFT_IS_DOWN){
				clear_back(true);
			} else {
				delete_char();
			}
			return true;


		case sf::Keyboard::Return: // submit text
			{
				std::string buf = get_buffer(); // trimmed of outer whitespace
				if (buf.find(" ") == std::string::npos && !buf.empty()){
					submit(get_buffer());
				} else {
					field_speaker->play("error.wav");
				}
			}
			return true;


		case sf::Keyboard::Left: // move cursor back
			if (LSHIFT_IS_DOWN){
				shift_cursor(vb::TOP);
			} else {
				shift_cursor(vb::UP);
			}
			return true;


		case sf::Keyboard::Right: // move cursor forward
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				shift_cursor(vb::BOTTOM);
			} else {
				shift_cursor(vb::DOWN);
			}
			return true;


		case sf::Keyboard::Escape: // close prompt pop-up
			p.engage_with(p.rack_chooser);
			p.draw_list.pop_back();
			delete this; // destroy self, free the memory
			return true;
		}
	}
	return false;
}




