#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <Debug.hpp>
#include <Sound.hpp>
#include <cmath>
#include <thread>

namespace {
#define GROW 1.0f
#define SHRINK -1.0f
}

class Button : public sf::Drawable {

	int x,y,w,h;
	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Color idleColor = sf::Color(231, 146, 71, 255);
	sf::Color hoverColor = sf::Color(132, 231, 47, 255);
	sf::Text bText;
	std::function<void(void)> onPress;

	bool isHovered = false;
	static std::shared_ptr<aud::Sound> pressSound;
	static std::shared_ptr<aud::Sound> hoverSound;
	static sf::Font font;

	static int hoverScaleAmount;
	static int hoverScaleSpeed;

	std::thread* anim;
	bool animate = false;
	int animStamp = 0;


public:

	Button(int _w, int _h, const std::string _text, std::function<void(void)> _onPress) : w(_w), h(_h), onPress(_onPress){
		box = sf::RectangleShape(sf::Vector2f(w,h));
		box.setFillColor(idleColor);
		box.setOutlineThickness(1);
		box.setOutlineColor(sf::Color::Black);

		//Button::font.loadFromFile("res/sansation.ttf");
		// center rectangles pivot
		box.setOrigin(w/2, h/2);

		//bText = sf::Text(_text, Button::font, (unsigned int) (h/1.7)); // font size a function of button height
		bText.setFillColor(sf::Color::Black); // set font color
		sf::FloatRect textBounds = bText.getLocalBounds();
		bText.setOrigin((int)(textBounds.width/2), (int)(h/2.4));

	}


	void setXY(int _x, int _y) {
		x = _x;
		y = _y;
		zone = sf::Rect<int>(x-w/2,y-h/2,w,h);
		box.setPosition(x, y);
		bText.setPosition(x,y);
	};


	int getWidth() const {
		return w;
	};


	int getHeight() const {
		return h;
	};


	void setColor(sf::Color c){
		box.setFillColor(c);
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(box); // draw the button box
		target.draw(bText); // draw the button text
	}


	void checkPress(int mouseX, int mouseY){
		if (zone.contains(mouseX, mouseY)){ // this button was pressed
			Button::pressSound->play();
			this->onPress();
		}
	}


	void checkHover(int mouseX, int mouseY){
		if (isHovered == false && zone.contains(mouseX, mouseY)){ // this button was pressed

			isHovered = true;
			Button::hoverSound->play();
			box.setFillColor(hoverColor);

			if (animate){
				animate = false;
				anim->join(); // wait for shrink to stop
				delete anim;
			}
			anim = new std::thread(&Button::hoverScaleButton, this, GROW);


		} else if (isHovered == true && !zone.contains(mouseX, mouseY)){

			isHovered = false;
			box.setFillColor(idleColor);
			
			if (animate){
				animate = false;
				anim->join(); // wait for grow to stop
				delete anim;
			}
			anim = new std::thread(&Button::hoverScaleButton, this, SHRINK); // starts right when its created

			//Coroutine(&Button::hoverScaleButton, this).launch();
		}
	}


	void hoverScaleButton(float scaleType){
		animate = true;
		int i;
		for (i = animStamp; i < Button::hoverScaleAmount && animate; ++i){
			box.setSize(box.getSize() + scaleType * sf::Vector2f(1, 0));
			box.setPosition(box.getPosition() - scaleType * sf::Vector2f(1/2.0f, 0));
			sf::sleep(sf::milliseconds(Button::hoverScaleSpeed));
		}
		animStamp = Button::hoverScaleAmount - i;
		animate = false;
	}


	static void cleanup(){
		Button::pressSound.reset();
		Button::hoverSound.reset();
	}

};


