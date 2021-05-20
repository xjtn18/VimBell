#include <TextField.hpp>


TextField::TextField(const char* init_content, int _x, int _y, int _w, int _h)
	: content(new char[50]), x(_x), y(_y), w(_w), h(_h), \
		box(sf::RectangleShape(sf::Vector2f(w, h))), cursor(TextCursor(x - w/2 + 24, y, 30, h-14))
{
	int len = strlen(init_content);
	for (int i = 0; i < len; i++){
		content[i] = init_content[i];
	}
	box.setOrigin(w/2, h/2);
	box.setPosition(x, y);
	box.setFillColor(sf::Color(231, 146, 71, 255));
}


void TextField::write(){
	// write a character to the content
}


void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	target.draw(cursor);
}





TextCursor::TextCursor(int _x, int _y, int _w, int _h)
	:  x(_x), y(_y), w(_w), h(_h), \
		show(true), stopped(false), box(sf::RectangleShape(sf::Vector2f(w,h))), hang_ms(400)
{
	box.setOrigin(w/2, h/2);
	box.setPosition(x, y);
	box.setFillColor(sf::Color::Black);

	task = std::async(std::launch::async, [&]{
	while(task_killer.wait_for(hang_ms)){
		if (show){
			hang_ms = 300ms;
		} else {
			hang_ms = 600ms;
		}
		show = !show;
	}
	});

}


TextCursor::~TextCursor(){
	task_killer.kill();
	//task.wait(); // not sure if this is necessary
}



void TextCursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (show){
		target.draw(box); // draw the button box
	}
}





