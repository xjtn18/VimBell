#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>
#include <Line.hpp>
#include <TextCursor.hpp>



class TextField : public sf::Drawable {
public:
	static void setup();
	static void cleanup();

	TextField(){};
	TextField(const char* init_content, jb::Transform tf, bool _active);
	~TextField();

	void engage(bool value);
	void write(const char character);
	void delete_char();
	void shift_cursor(jb::Direc direction);
	void clear_buffer(bool audible = false);
	void fill(std::string content);
	std::string get_buffer() const;
	void draw_buffer(sf::RenderTarget& target) const;
	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	static sf::Font font;
	static aud::Speaker* field_speaker;

	jb::Transform tf;
	int bufmax;
	sf::RectangleShape box; // the text box itself
	TextCursor cursor;
	Line line;
	bool engaged;
};


