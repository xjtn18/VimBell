#pragma once
#include <jb.hpp>
#include <cmath>


struct Program; // FD


struct Entity : public sf::Drawable {
	jb::Transform tf;
	bool engaged;

	Entity(){}
	Entity(jb::Transform _tf)
		: tf(_tf), engaged(false)
	{ }

	Entity(jb::Transform _tf, bool _engaged)
		: tf(_tf), engaged(_engaged)
	{ }

	Entity(const Entity& other) = default;
	virtual ~Entity(){};


	void round_position(){
		tf.x = round(tf.x);
		tf.y = round(tf.y);
	}
	
	void move(float x_offset, float y_offset, float mag, float dt){
		tf.x += (x_offset * mag * dt);
		tf.y += (y_offset * mag * dt);
	};

	// static UI entities do not require defining these
	virtual void engage(bool value)  {}
	virtual void update(float dt)    {}
	virtual bool handler(sf::Event& event, Program& p) {return false;}

	// every entity will define a draw method
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;


};


