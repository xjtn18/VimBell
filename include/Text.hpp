#include <SFML/Graphics.hpp>
#include <Entity.hpp>

struct Text : public Entity {
	sf::Text txt;

	Text(jb::Transform _tf, const char* content, sf::Font& _font, int _fontsize);

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

