#pragma once
#include <Entity.hpp>
#include <functional>


struct TextCursor : public Entity {

	sf::RectangleShape box; // the visual of the text cursor
	float lerp, blink_target;
	std::function<float(float)> lerpf;


	TextCursor(){}
	TextCursor(vb::Transform _tf);
	~TextCursor();

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void translate(const int new_x, const int new_y);
	void move(int dir);
	void set_pos(int index, vb::Transform plane_ref);

	int get_width() const {
		return tf.w;
	}
};



