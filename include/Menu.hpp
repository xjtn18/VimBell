#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <Debug.hpp>
#include <vector>
#include <initializer_list>


class Menu : public sf::Drawable {
	//
	// A vertical arrangment of buttons.
	// params:
	// 		padding: amount of space in pixels between each button
	// 		x and y: position of the menu
	// 		l: init list of Button objects
	//
	std::vector<Button> buttons;

public:

	Menu(){}

	Menu(int padding, int _x, int _y, std::initializer_list<Button> l) : buttons(l) {

		int bY = _y; // button y placement
		for (int i = 0; i < buttons.size(); ++i){ // set each button location
			Button& button = buttons[i];
			button.setXY(_x, bY); // all buttons have the same x coordinate
			if (i != buttons.size()-1){ // if this isnt the last button in the menu
				bY += button.getHeight()/2 + buttons[i+1].getHeight()/2 + padding; // update for next button placement
			}
		}
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const Button& button : buttons){ // draw each button
			target.draw(button);
		}
	}


	void setButtonColor(sf::Color c){
		for (Button& button : buttons){
			button.setColor(c);
		}
	}


	void checkPress(int mouseX, int mouseY){
		for (Button& button : buttons){
			button.checkPress(mouseX, mouseY);
		}
	}


	void checkHover(int mouseX, int mouseY){
		for (Button& button : buttons){
			button.checkHover(mouseX, mouseY);
		}
	}


};

