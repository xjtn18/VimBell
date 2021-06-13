#include <VStack.hpp>


VStack::VStack(int x, int y, int _padding, std::initializer_list<Entity*> l)
	: padding(_padding), entities(l)
{
	int _y = y;
	for (auto e : entities){
		e->tf.x = x;
		e->tf.y = _y;
		_y += e->tf.h + padding;
	}
}


VStack::~VStack(){}


void VStack::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto& e : entities){
		target.draw(*e);
	}
}
