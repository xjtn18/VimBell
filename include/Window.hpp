#pragma once
#include <SFML/Window.hpp>
#include <Debug.hpp>


class Window {
	
	int width; // window width
	int height; // window height
	sf::RenderWindow* window;

public:
	Window(){}
	Window(int _width, int _height) : width(_width), height(_height){
		sf::ContextSettings settings;
		settings.antialiasingLevel = 16;
		window = new sf::RenderWindow(sf::VideoMode(_width, _height), "jBell", sf::Style::Titlebar | sf::Style::Close, settings);
	}

	~Window(){
		delete window;
	}

	inline sf::RenderWindow& get_window(){
		return *window;
	}

	inline int get_width(){
		return width;
	}

	inline int get_height(){
		return height;
	}

};

