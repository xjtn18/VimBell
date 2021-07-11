#pragma once

#include <jb.hpp>
#include <Line.hpp>
#include <Speaker.hpp>
#include <TextCursor.hpp>
#include <Entity.hpp>




class TextField : public Entity {
public:
	static void cleanup();

	TextField(){};
	TextField(const char* init_content, jb::Transform tf, bool _engaged = false);
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
	void handler(sf::Event& event, Program& p);


private:
	static aud::Speaker* field_speaker;

	float lerp;
	int bufmax;
	sf::RectangleShape box; // the text box itself
	TextCursor cursor;
	Line line;
	bool engaged;
};


