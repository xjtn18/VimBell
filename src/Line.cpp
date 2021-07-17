#include <Line.hpp>
#include <unordered_set>



Line::Line(jb::Transform _tf, const char* initial, int _fontsize, int _margin, int _spacing, sf::Color _fontcolor)
	: Entity(_tf),
		index(0),
		spacing(_spacing),
		margin(_margin),
		fontsize(_fontsize),
		fontcolor(_fontcolor)
{
	for (int i = 0; i < strlen(initial); ++i){
		insert_char(initial[i]);
	}
}




void Line::insert_char(char c){
	sf::Text txt(c, FONT_LIBMONO, fontsize); // TODO: This should create char with font given as param to constructor.
	sf::FloatRect b = txt.getLocalBounds();
	int shift = 0;
	SET<char> shifted = {'b', 't', 'S', 'm', 'n', 'M', 'J'}; // @NOTE these letters need to be shifted left
	if (is_in(c, shifted)) shift = 1;
	txt.setOrigin((int)(b.left + b.width/2 + shift), (int)(fontsize * .75 - 2));
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

void Line::clear_back(){
	line.erase(line.begin(), line.begin() + index);
	index = 0;
	repos_text();
}

void Line::clear_all(){
	line.clear();
	index = 0;
}


void Line::set(const char* content){
	clear_all();
	for (int j = 0; j < strlen(content); ++j){
		insert_char(content[j]);
	}
}


void Line::repos_text(){
	int offset;
	for (int i = 0; i < line.size(); ++i){
		offset = i * spacing;
		auto bounds = line[i].getLocalBounds();
		line[i].setPosition((int)tf.x + margin + offset, (int)tf.y); // TODO: Text chars not aligned as sf::Text would be.
	}
}


std::string Line::get_string() const {
	std::string result;
	for (int i = 0; i < line.size(); ++i){
		result += line[i].getString();
	}
	return result;
}



void Line::engage(bool value){
	if (!value){ // if disengaging, reset font color to default (if its in the middle of blinking)
		if (line.size() > 0){
			line[index].setFillColor(sf::Color(50, 50, 50));
		}
	}
}


void Line::update(float dt){
	// set character colors
	for (int i = 0; i < line.size(); ++i){
		if (i != index){
			line[i].setFillColor(sf::Color(50, 50, 50));
		} else {
			int rtarget = 255;
			int gtarget = 101;
			int btarget = 74;
			float x = 180/PI * lerp;

			sf::Color last = line[index].getFillColor();
			last.r = (rtarget - 50) * lerpf(x) + 50;
			last.g = (gtarget - 50) * lerpf(x) + 50;
			last.b = (btarget - 50) * lerpf(x) + 50;
			line[index].setFillColor(last);
		}
	}
}


void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& c : line){
		target.draw(c);
	}
}


