#pragma once
#include <jb.hpp>
#include <thread>

class Rack;

class ThreadClock {
public:

	ThreadClock(std::shared_ptr<Rack> _rack);
	void callback();
	void stop();

private:
	std::thread thr;
	std::atomic<bool> stopped;
	std::shared_ptr<Rack> rack;
};

