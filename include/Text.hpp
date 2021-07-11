#include <SFML/Graphics.hpp>
#include <Entity.hpp>

struct Text : public Entity {
	sf::Text txt;
	sf::FloatRect max_bounds;

	Text(jb::Transform _tf, std::string content, sf::Font& _font, int _fontsize);

	void center_xaxis();
	void center_yaxis();

	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

