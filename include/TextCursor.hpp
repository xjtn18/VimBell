#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


class TextCursor : public sf::Drawable {
public:
	TextCursor();
	TextCursor(jb::Transform tf);
	~TextCursor();

	void update(float delta_time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void translate(const int new_x, const int new_y);
	void reset_blink_state();
	void move(int dir);

	int get_width() const {
		return tf.w;
	}

private:
	jb::Transform tf;
	sf::RectangleShape box; // the visual of the text cursor
	float blink_lerp, blink_target, blink_rate;
	
};



