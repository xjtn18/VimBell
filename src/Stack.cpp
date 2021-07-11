#include <Stack.hpp>
#include <algorithm>


VStack::VStack(jb::Transform _tf, int _padding, std::initializer_list<Entity*> l)
	: Entity(_tf),
	  padding(_padding),
	  entities(l)
{
}

VStack::~VStack(){}



void VStack::clear(){
	for (int i = 0; i < entities.size(); ++i){
		delete entities[i];
	}
	entities.clear();
	tf.h = 0;
}


void VStack::insert(int index, Entity *entity){
	if (index == -1){
		entities.push_back(entity);
	} else {
		entities.insert(entities.begin() + index, entity);
	}
}




void VStack::update(float dt) {
	tf.h = 0;
	float _y = tf.y;
	for (auto& e : entities){
		//e->tf.x = tf.x; // NOTE: X of entities will not change as the stack moves
		e->tf.y = _y;
		_y += e->tf.h + padding;
		e->update(dt);

		tf.h += e->tf.h + padding;
		tf.w = std::max(e->tf.w, tf.w);
	}
	tf.h -= padding;
}


void VStack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& e : entities){
		target.draw(*e);
	}
}






HStack::HStack(jb::Transform _tf, int _padding, std::initializer_list<Entity*> l)
	: Entity(_tf),
	  padding(_padding),
	  entities(l)
{
}

HStack::~HStack(){}



void HStack::clear(){
	for (int i = 0; i < entities.size(); ++i){
		delete entities[i];
	}
	entities.clear();
	tf.w = 0;
}


void HStack::insert(int index, Entity *entity){
	if (index == -1){
		entities.push_back(entity);
	} else {
		entities.insert(entities.begin() + index, entity);
	}
}




void HStack::update(float dt) {
	tf.w = 0;
	float _x = tf.x;
	for (auto& e : entities){
		e->tf.y = tf.y;
		e->tf.x = _x;
		_x += e->tf.w + padding;
		e->update(dt);

		tf.w += e->tf.w + padding;
		tf.h = std::max(e->tf.h, tf.h);
	}
	tf.w -= padding;
}


void HStack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& e : entities){
		target.draw(*e);
	}
}


