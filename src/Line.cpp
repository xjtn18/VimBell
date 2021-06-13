#include <Line.hpp>


Line::Line(const char* initial, int _fontsize, jb::Transform _tf, int _margin, int _spacing, sf::Color _fontcolor)
	 : fontsize(_fontsize),
		spacing(_spacing),
		index(0),
		tf(_tf),
		margin(_margin),
		fontcolor(_fontcolor)
{
	 font.loadFromFile("res/fonts/incon.ttf");
	 for (int i = 0; i < strlen(initial); ++i){
		 insert_char(initial[i]);
	 }
}


Line& Line::operator =(const Line& from){
	if (&from != this){
		font = from.font;
		fontsize = from.fontsize;
		spacing = from.spacing;
		index = 0;
		tf = from.tf;
		margin = from.margin;
		fontcolor = from.fontcolor;
		font.loadFromFile("res/fonts/incon.ttf");

		line.clear();
		for (int i = 0; i < from.line.size(); ++i){
			std::string s = from.line[i].getString();
			insert_char(s[0]);
		}
	}
	return *this;
}


void Line::insert_char(char c){
	 sf::Text txt(c, font, fontsize);
	 sf::FloatRect b = txt.getLocalBounds();
	 txt.setOrigin((int)(b.left + b.width/2), (int)(fontsize * .75 - 2)); // this is vital
	 int offset = index * spacing;
	 txt.setPosition((int)(tf.x + margin + offset), (int)(tf.y));
	 txt.setFillColor(fontcolor);
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
	for (int i = 0; i < line.size(); ++i){
		target.draw(line[i]);
	}
}

