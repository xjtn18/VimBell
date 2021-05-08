#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


namespace img {

	class Image : public sf::Drawable {
		sf::Image image;
		sf::Texture tex;
		sf::Sprite sprite;
		int w, h;
		
	public:
		Image(const char* filename){
			image.loadFromFile(filename);
			sf::Vector2u imageDim = image.getSize();
			w = imageDim.x;
			h = imageDim.y;
			tex.loadFromImage(image);
			sprite.setTexture(tex);
		}


		int getWidth() const {
			return w;
		}

		int getHeight() const {
			return h;
		}

		void setXY(int x, int y){
			sprite.setPosition(x, y);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(sprite);
		}

	};




};
