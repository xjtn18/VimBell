#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


class Line : public sf::Drawable {
public:
	std::vector<sf::Text> line;
	int size, fontsize, spacing, index, margin;
	sf::Font font;
	jb::Transform tf;
	sf::Color fontcolor;

	Line(){}
	Line(const char* initial, int _fontsize, jb::Transform _tf, int _margin, int _spacing, sf::Color _fontcolor);
	Line(const Line& line) = default;
	Line& operator =(const Line& from);

	void insert_char(char c);
	void remove_char();
	void clear();
	void clear_all();
	void set(const char* content);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

