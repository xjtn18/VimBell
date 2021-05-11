#pragma once
#include <SFML/Graphics.hpp>

#include <Button.hpp>
#include <Debug.hpp>
#include <jb.hpp>

#include <vector>
#include <initializer_list>


namespace {
	void clamp(int& value, const int& low, const int& high){
		// clamps the value to the bounds given
		if (value < low) value = low;
		else if (value >= high) value = high - 1;
	}
}


class Menu : public sf::Drawable {
	//
	// A vertical arrangment of buttons.
	//
	std::vector<Button> buttons;		// vector of menu elements
	int select_index;						// index that represents location in the list
	int x, y, padding;					// x,y location of menu; padding distance between menu elements

public:

	Menu(){}

	Menu(int padding, int _x, int _y, std::initializer_list<Button> l)
		: buttons(l), select_index(0), x(_x), y(_y)
		// @params:
		// 	padding: amount of space in pixels between each button
		// 	x and y: position of the menu
		// 	l: init list of Button objects
	{
		this->update();
		buttons[0].select(); // set initial selection when menu loads
	}
	

	void update(){
		// call this function whenever the menu is created or when menu layout changes
		int bY = y; // button y placement
		for (int i = 0; i < buttons.size(); ++i){ // set each button location
			Button& button = buttons[i];
			button.setXY(x, bY); // all buttons have the same x coordinate
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
	
	
	void selectMove(jb::Direc MOVE){
		buttons[select_index].deselect(); // de-select current elem
		select_index += MOVE;
		clamp(select_index, 0, buttons.size());
		buttons[select_index].select(); // select new elem
	}


	void activateSelection(){
		buttons[select_index].activate();
	}


	void duplicateButton(){
		buttons.insert(buttons.begin() + select_index + 1, Button(300, 60, "start", buttons[select_index].getProcedure()));
		//TODO: Make sure that deleting parent elem does not delete procedure of child elem that was duplicated from it.
		selectMove(jb::DOWN); // move selector to the newly created elem
		update();
	}

};

