#pragma once
#include <Entity.hpp>
#include <functional>


struct Line : public Entity {
	std::vector<sf::Text> line;
	int fontsize, spacing, index, margin;
	sf::Color fontcolor;
	std::function<float(float)> lerpf = [](float x) -> float {return x;};
	float lerp;


	Line(){}
	Line(jb::Transform _tf, const char* initial, int _fontsize, int _margin, int _spacing, sf::Color _fontcolor);
	Line(const Line& line) = default;

	void insert_char(char c);
	void remove_char();
	void clear_back();
	void clear_all();
	void set(const char* content);
	std::string get_string() const;

	void engage(bool value);
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void repos_text();
};


