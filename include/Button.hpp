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
	sf::String text;
	std::function<void(void)> procedure;

	bool is_hovered = false;
	static sf::Font font;

	static int hoverScaleAmount;
	static int hoverScaleSpeed;

	std::thread* anim;
	bool animate = false;
	int animStamp = 0;



public:

	static void SETUP(){
		Button::font.loadFromFile("res/fonts/incon.ttf");
	}

	Button(int _w, int _h, const std::string _text, std::function<void(void)> _procedure)
		: w(_w), h(_h), text(_text), procedure(_procedure)
	{
		box = sf::RectangleShape(sf::Vector2f(w,h));
		box.setFillColor(idleColor);
		box.setOutlineThickness(1);
		box.setOutlineColor(sf::Color::Black);
		box.setOrigin(w/2, h/2);

		bText = sf::Text(text, Button::font, (unsigned int) (h/1.7));
		bText.setFillColor(sf::Color::Black); // set font color
		sf::FloatRect textBounds = bText.getLocalBounds();
		bText.setOrigin((int)(textBounds.width/2), (int)(h/2.4));
	}


	Button(const Button& other) // copy constructor
		: w(other.w), h(other.h), text(other.text), procedure(other.procedure), \
		  box(other.box), bText(other.bText)
	{
		setXY(other.x, other.y);
	}

	Button& operator =(const Button& other) // assignment operator
	{
		if (this != &other){
			w = other.w;
			h = other.h;
			text = other.text;
			procedure = other.procedure;
			setXY(other.x, other.y);
		}
		return *this;
	}

	static void cleanup(){
	}


	void setXY(int _x, int _y) {
		x = _x;
		y = _y;
		zone = sf::Rect<int>(x-w/2,y-h/2,w,h);
		box.setPosition(x, y);
		bText.setPosition(x, y);
	};


	int get_width() const {
		return w;
	};


	int get_height() const {
		return h;
	};


	void set_color(sf::Color c){
		box.setFillColor(c);
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(box); // draw the button box
		target.draw(bText); // draw the button text
	}


	void check_press(int mouseX, int mouseY){
		if (zone.contains(mouseX, mouseY)){ // this button was pressed
			this->procedure();
		}
	}


	void check_hover(int mouseX, int mouseY){
		if (is_hovered == false && zone.contains(mouseX, mouseY)){ // this button was pressed

			is_hovered = true;
			box.setFillColor(hoverColor);

			if (animate){
				animate = false;
				anim->join(); // wait for shrink to stop
				delete anim;
			}
			anim = new std::thread(&Button::hover_scale_button, this, GROW);


		} else if (is_hovered == true && !zone.contains(mouseX, mouseY)){

			is_hovered = false;
			box.setFillColor(idleColor);
			
			if (animate){
				animate = false;
				anim->join(); // wait for grow to stop
				delete anim;
			}
			anim = new std::thread(&Button::hover_scale_button, this, SHRINK); // starts right when its created

			//Coroutine(&Button::hoverScaleButton, this).launch();
		}
	}



	void hover_scale_button(float scaleType){
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


	void select(){
		box.setFillColor(hoverColor);

		if (animate){
			animate = false;
			anim->join(); // wait for shrink to stop
			delete anim;
		}
		//anim = new std::thread(&Button::hoverScaleButton, this, GROW);
	}


	void deselect(){
		box.setFillColor(idleColor);
		
		if (animate){
			animate = false;
			anim->join(); // wait for grow to stop
			delete anim;
		}
		//anim = new std::thread(&Button::hoverScaleButton, this, SHRINK); // starts right when its created
	}

	void activate(){
		this->procedure();
	}

	std::function<void(void)> get_procedure(){
		return this->procedure;
	}




};


