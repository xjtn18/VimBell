#pragma once
#include <SFML/Window.hpp>

class WindowWrapper {
	
	int width; // window width
	int height; // window height
	sf::RenderWindow* window;

public:
	WindowWrapper(int _width, int _height) : width(_width), height(_height){
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;
		window = new sf::RenderWindow(sf::VideoMode(_width, _height), "jBell", sf::Style::Titlebar | sf::Style::Close, settings);
	}

	~WindowWrapper(){
		delete window;
	}

	inline sf::RenderWindow* getWindow(){
		return window;
	}

	inline int getWindowWidth(){
		return width;
	}

	inline int getWindowHeight(){
		return height;
	}

};

