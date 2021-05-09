#pragma once
#include <jb.hpp>
#include <Alarm.hpp>


class Rack {
public:

	Rack();
	~Rack();
	void add_alarm();
	void query_active_alarms(const jb::Time t);

private:
	std::vector<Alarm> alarms;


};


