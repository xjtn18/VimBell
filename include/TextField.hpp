#pragma once

#include <Entity.hpp>
#include <Line.hpp>
#include <TextCursor.hpp>


// FD
namespace aud {
	struct Speaker;
}


struct TextField : public Entity {
	static aud::Speaker* field_speaker;
	static void cleanup();

	float lerp;
	int bufmax;
	sf::RectangleShape box; // the text box itself
	TextCursor cursor;
	Line line;


	TextField(){};
	TextField(jb::Transform _tf, const char* init_content, bool _engaged = false);
	~TextField();

	void engage(bool value);
	void write(const char character);
	void delete_char();
	void shift_cursor(jb::Direc direction);
	void clear_back(bool audible = false);
	void fill(std::string content);
	void clear_all();
	std::string get_buffer() const;
	void reset();
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool handler(sf::Event& event, Program& p);

};


