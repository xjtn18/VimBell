#include <Line.hpp>


Line::Line(const char* initial, int _fontsize, jb::Transform _tf, int _margin, int _spacing, sf::Color _fontcolor)
	: fontsize(_fontsize),
	  spacing(_spacing),
	  index(0),
	  tf(_tf),
	  margin(_margin),
	  lerp(0),
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

	line.insert(line.begin() + index, txt);
	index++;
	repos_text();
}


void Line::remove_char(){
	// shift all later text backward
   line.erase(line.begin() + index-1);
   index--;
	repos_text();
}

void Line::clear(){
	line.erase(line.begin(), line.begin() + index);
	index = 0;
	repos_text();
}

void Line::clear_all(){
	line.clear();
	index = 0;
}


void Line::set(const char* content){
	int len = strlen(content);
	for (int j = 0; j < len; ++j){
		insert_char(content[j]);
	}
}


void Line::repos_text(){
	for (int i = 0; i < line.size(); ++i){
		int offset = i * spacing;
		line[i].setPosition((int)(tf.x + margin + offset), (int)(tf.y));
	}
}


void Line::reset_lerp(){
	lerp = 0;
}


void Line::update(float dt){
	// set text colors
	for (int i = 0; i < line.size(); ++i){
		if (i != index){
			line[i].setFillColor(sf::Color(50, 50, 50));
		} else {
			line[index].setFillColor(sf::Color(255, 101, 74));

			float rate = 0.05;
			int rtarget = 255;
			int gtarget = 101;
			int btarget = 74;
			float inc = rate * dt;
			lerp += inc;
			if (lerp >= 360) lerp = 0;
			float x = 180/PI * lerp;
			auto blink_func = [=] (float x) -> float { return pow(-pow(sin(x - 0.6f), 18) + 1, 80); };
			sf::Color last = line[index].getFillColor();
			last.r = (rtarget - 50) * blink_func(x) + 50;
			last.g = (gtarget - 50) * blink_func(x) + 50;
			last.b = (btarget - 50) * blink_func(x) + 50;
			line[index].setFillColor(last);
		}
	}

}


void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& c : line){
		target.draw(c);
	}
}

