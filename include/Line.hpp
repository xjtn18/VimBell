#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


class Line : public sf::Drawable {
public:
	std::vector<sf::Text> line;
	int size, fontsize, spacing, index, margin;
	sf::Font font;
	jb::Transform tf;

	Line(){};
	Line(const char* initial, int _fontsize, jb::Transform _tf, int _margin, int _spacing);
	Line(const Line& line) = default;

	void insert_char(char c);
	void remove_char();
	void clear();
	void set(const char* content);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

