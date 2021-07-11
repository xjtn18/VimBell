#include <Image.hpp>


Image::Image(jb::Transform _tf, const char* filename)
	: Entity(_tf)
{
	image.loadFromFile(filename);
	sf::Vector2u imageDim = image.getSize();
	tf.w = imageDim.x;
	tf.h = imageDim.y;
	tex.loadFromImage(image);
	sprite.setTexture(tex);
	sprite.setOrigin(tf.w/2, tf.h/2);
}


void Image::update(float dt){
	sprite.setPosition(tf.x, tf.y);
	sprite.rotate(dt);
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}
