#pragma once
#include <jb.hpp>
#include <Alarm.hpp>


class Rack {
public:
	static std::shared_ptr<Rack> currentRack;

	Rack();
	~Rack();
	static void cleanup();
	void add_alarm();
	void query_active_alarms(const jb::Time t);

private:
	std::vector<Alarm> alarms;


};


