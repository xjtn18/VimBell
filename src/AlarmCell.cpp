#include <AlarmCell.hpp>

sf::Font AlarmCell::font;
sf::Color AlarmCell::idleColor = sf::Color(80, 80, 80, 255);
sf::Color AlarmCell::hoverColor = sf::Color(132, 231, 47, 255);


void AlarmCell::setup(){
   AlarmCell::font.loadFromFile("res/fonts/incon.ttf");
}


AlarmCell::AlarmCell(int _w, int _h, const std::string _text)
	: w(_w), h(_h), text(_text)
{
	box = sf::RectangleShape(sf::Vector2f(w,h));
	box.setFillColor(idleColor);
	//box.setOrigin(w/2, h/2);

	bText = sf::Text(text, AlarmCell::font, (unsigned int) (h/1.85));
	bText.setFillColor(sf::Color::Black); // set font color
	sf::FloatRect textBounds = bText.getLocalBounds();
	bText.setOrigin(0, (int)(h/2)-5);
}


AlarmCell::AlarmCell(const AlarmCell& other) // copy constructor
	: w(other.w), h(other.h), text(other.text),
	  box(other.box), bText(other.bText)
{
	set_xy(other.x, other.y);
}


AlarmCell& AlarmCell::operator =(const AlarmCell& other) // assignment operator
{
	if (this != &other){
		w = other.w;
		h = other.h;
		text = other.text;
		set_xy(other.x, other.y);
	}
	return *this;
}


void AlarmCell::cleanup(){

}


void AlarmCell::set_xy(int _x, int _y) {
	x = _x;
	y = _y;
	zone = sf::Rect<int>(x-w/2,y-h/2,w,h);
	box.setPosition(x-w/2, y);
	bText.setPosition(x-w/2 + 25, y+h/1.8);
};


int AlarmCell::get_width() const {
	return w;
};


int AlarmCell::get_height() const {
	return h;
};


void AlarmCell::set_color(sf::Color c){
	box.setFillColor(c);
}


void AlarmCell::select(){
	box.setFillColor(hoverColor);
}


void AlarmCell::deselect(){
	box.setFillColor(idleColor);
}


void AlarmCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box); // draw the button box
	target.draw(bText); // draw the button text
}



