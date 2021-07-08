#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>
#include <functional>


class TextCursor : public sf::Drawable {
public:
	std::function<float(float)> lerpf;

	TextCursor(){}
	TextCursor(jb::Transform tf);
	~TextCursor();

	void update(float dt, float lerp);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void translate(const int new_x, const int new_y);
	void move(int dir);
	void set_pos(int index, jb::Transform plane_ref);

	int get_width() const {
		return tf.w;
	}

private:
	jb::Transform tf;
	sf::RectangleShape box; // the visual of the text cursor
	float blink_target, blink_rate;
};



