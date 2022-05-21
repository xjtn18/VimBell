#pragma once
#include <vb.hpp>

// FD
namespace aud {
	struct Speaker;
}

struct Alarm {
	///////// members /////////
	static aud::Speaker *alarm_speaker;
	static void silence();

	vb::Time        target;
	bool            active;
	std::string     msg;
	std::string     alarm_name;
	int             stacc;
	int             stacc_interval;
	///////////////////////////

	Alarm(){};
	Alarm(vb::Time initTarget, std::string initMsg, int initStacc, int initStaccInterval, bool initActive);
	Alarm(const Alarm& other) = default;
	static void cleanup();
	~Alarm();

	inline void toggle(){
		active = !active;
	}

	void add_to_stack();
	bool remove_from_stack();
	void alter_stacc_interval(int i);
	bool operator<(const Alarm& other) const;

	bool query(vb::Time t);
	void trigger();



};


