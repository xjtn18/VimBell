#pragma once
#include <jb.hpp>
#include <Sound.hpp>
using namespace aud;


class Alarm {

public:
	Alarm();
	Alarm(jb::Time initTarget, std::string initMsg = "default", bool initActive = false);
	Alarm(const Alarm& other);
	static void cleanup();
	~Alarm();


	inline const jb::Time& get_target() const {
		return this->target;
	}

	inline const bool& is_active() const {
		return this->active;
	}

	inline const std::string& get_msg() const {
		return this->msg;
	}

	void query(jb::Time t);
	void trigger();
	void toggle();
	void set_target(jb::Time new_target);


	static void silence();

private:
	jb::Time 		target;
	bool 				active;
	std::string 	msg;
	std::string 	sound_name;

	// statics
	static Sound* 	global_alarm_speaker;
};



