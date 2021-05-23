#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


class TextCursor : public sf::Drawable {
public:
	TextCursor();
	TextCursor(jb::Transform tf);
	~TextCursor();
	inline int get_width() const;
	void set_xy(const int new_x, const int new_y);
	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void translate(const int new_x, const int new_y);
	void reset_blink_state();
	void move(int dir);

private:
	jb::Transform tf;
	sf::RectangleShape box; // the visual of the text cursor
	std::atomic<bool> show;
	float blink_lerp, blink_target, blink_rate;
	
};




class TextField : public sf::Drawable {
public:
	TextField(){};
	TextField(const char* init_content, jb::Transform tf, bool _active);
	~TextField();
	void write(const char character);
	void delete_char();
	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void draw_buffer(sf::RenderTarget& target) const;
	void set_active(bool value);
	void clear_buffer();

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
	bool active;
};


