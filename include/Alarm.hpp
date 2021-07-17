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
	///////////////////////////

	Alarm(){};
	Alarm(jb::Time initTarget, std::string initMsg = "default", bool initActive = true);
	Alarm(const Alarm& other);
	static void cleanup();
	~Alarm();

	inline void toggle(){
		active = !active;
	}

	bool operator<(const Alarm& other) const;

	void query(jb::Time t);
	void trigger();



};


