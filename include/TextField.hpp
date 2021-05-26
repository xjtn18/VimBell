#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>
#include <TextCursor.hpp>



class TextField : public sf::Drawable {
public:
	TextField(){};
	TextField(const char* init_content, jb::Transform tf, bool _active);
	~TextField();

	static void setup();
	void engage(bool value);
	void write(const char character);
	void delete_char();
	void clear_buffer();
	void update(float delta_time);
	void draw_buffer(sf::RenderTarget& target) const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	inline std::string get_buffer() const {
		return (std::string) buffer;
	}



private:
	jb::Transform tf;
	char* buffer;
	std::vector<sf::Text> tvec;
	int buffer_index, bufmax;
	sf::RectangleShape box; // the text box itself
	TextCursor cursor;
	static sf::Font font;
	bool engaged;
};


