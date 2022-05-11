#pragma once
#include <thread>
#include <memory>
#include <atomic>

struct Rack;
struct Program;

struct ThreadClock {
	ThreadClock(std::shared_ptr<Rack> _rack, Program& p);
	void callback(Program &p);
	void stop();

	std::thread thr;
	std::atomic<bool> stopped;
	std::shared_ptr<Rack> rack;
};

