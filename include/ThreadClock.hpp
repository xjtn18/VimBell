#pragma once
#include <jb.hpp>
#include <thread>

struct Rack;

struct ThreadClock {
	ThreadClock(std::shared_ptr<Rack> _rack);
	void callback();
	void stop();

	std::thread thr;
	std::atomic<bool> stopped;
	std::shared_ptr<Rack> rack;
};

