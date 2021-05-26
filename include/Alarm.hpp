#pragma once
#include <jb.hpp>
#include <Speaker.hpp>
using namespace aud;


class Alarm {

public:
	Alarm(){};
	Alarm(jb::Time initTarget, std::string initMsg = "default", bool initActive = true);
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

	inline void toggle(){
		active = !active;
	}

	inline void set_target(jb::Time new_target){
		target = new_target;
	}

	inline void set_message(std::string _msg){
		msg = _msg;
	}

	void query(jb::Time t);
	void trigger();

	static void silence();


private:
	jb::Time 		target;
	bool 				active;
	std::string 	msg;
	std::string 	sound_name;

	// statics
	static Speaker *alarm_speaker;
};



