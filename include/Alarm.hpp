#pragma once
#include <jb.hpp>
#include <Sound.hpp>


class Alarm {

public:
	Alarm(jb::Time initTarget, std::string initMsg = "", bool initActive = true);

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

	//inline void SetTriggerSound(){

	void query(jb::Time t);
	void trigger();

private:
	jb::Time target;
	std::string msg;
	bool active;
	aud::Sound snd;

};
