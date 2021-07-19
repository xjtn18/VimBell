#pragma once
#include <jb.hpp>
#include <Speaker.hpp>
using namespace aud;



struct Alarm {
	///////// members /////////
	static Speaker *alarm_speaker;
	static void silence();

	jb::Time 		target;
	bool 				active;
	std::string 	msg;
	std::string 	alarm_name;
	int 				stacc;
	int				stacc_interval;
	///////////////////////////

	Alarm(){};
	Alarm(jb::Time initTarget, std::string initMsg = "default", bool initActive = true);
	Alarm(const Alarm& other) = default;
	static void cleanup();
	~Alarm();

	inline void toggle(){
		active = !active;
	}

	void add_to_stack();
	bool remove_from_stack();
	bool operator<(const Alarm& other) const;

	void query(jb::Time t);
	void trigger();



};


