#include <Line.hpp>


Line::Line(const char* initial, int _fontsize, jb::Transform _tf, int _margin, int _spacing)
	 : size(strlen(initial)), line(strlen(initial)), fontsize(_fontsize), spacing(_spacing), index(0), tf(_tf), margin(_margin)
{
	 font.loadFromFile("res/fonts/incon.ttf");

	 for (int i = 0; i < size; ++i){
		  insert_char(initial[i]);
	 }
}

void Line::insert_char(char c){
	 sf::Text txt(c, font, fontsize);
	 sf::FloatRect b = txt.getLocalBounds();
	 txt.setOrigin((int)(b.left + b.width/2), (int)(fontsize * .75 - 2)); // this is vital
	 int offset = index * spacing;
	 txt.setPosition((int)(tf.x + margin + offset), (int)(tf.y));
	 txt.setFillColor(sf::Color(50,50,50));
	 line.push_back(txt);
	 index++;
}

void Line::remove_char(){
	 line.pop_back();
	 index--;
}

void Line::clear(){
	 line.clear();
	 index = 0;
}

void Line::set(const char* content){
	 int len = strlen(content);
	 for (int j = 0; j < len; ++j){
		  insert_char(content[j]);
	 }
}


void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	 for (auto& c : line){
		  target.draw(c);
	 }
}

