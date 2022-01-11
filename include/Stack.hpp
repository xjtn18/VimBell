#pragma once
#include <Entity.hpp>
#include <initializer_list>


struct VStack : public Entity {
	int padding;
	std::vector<Entity*> entities;


	VStack(){};
	VStack(jb::Transform _tf, int _padding, std::initializer_list<Entity*> l);
	~VStack();

	void clear();
	void insert(int index, Entity *entity);

	// overrides
	void update(float dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};


struct HStack : public Entity {
	int padding;
	std::vector<Entity*> entities;

	HStack(){};
	HStack(jb::Transform _tf, int _padding, std::initializer_list<Entity*> l);
	~HStack();

	void clear();
	void insert(int index, Entity *entity);

	// overrides
	void update(float dt) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};


