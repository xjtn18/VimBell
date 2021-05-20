#pragma once
#include <jb.hpp>
#include <SFML/Graphics.hpp>


#include <condition_variable>
#include <mutex>
#include <future>
#include <chrono>

using namespace std::literals::chrono_literals;

struct TimerKiller {
	// returns false if killed:
	template<class R, class P>
	bool wait_for( std::chrono::duration<R,P> const& time ) {
		std::unique_lock<std::mutex> lock(m);
		return !cv.wait_for(lock, time, [&]{return terminate;});
	}

	void kill() {
		std::unique_lock<std::mutex> lock(m);
		terminate=true;
		cv.notify_all();
	}

private:
	std::condition_variable cv;
	std::mutex m;
	bool terminate = false;
};






class TextCursor : public sf::Drawable {
public:
	TextCursor(int _x, int _y, int _w, int _h);
	~TextCursor();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	int x, y, w, h;
	sf::RectangleShape box; // the visual of the text cursor
	std::thread thr;
	std::atomic<bool> show, stopped;
	std::chrono::milliseconds hang_ms;
	std::future<void> task;
	TimerKiller task_killer;
};



class TextField : public sf::Drawable {
public:
	TextField(const char* init_content, int x, int y, int w, int h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void write();


private:
	char* content;
	int x, y, w, h;
	sf::RectangleShape box; // the visual of the text field
	TextCursor cursor;
};


