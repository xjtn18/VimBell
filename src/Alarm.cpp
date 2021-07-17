#include <Alarm.hpp>


/// statics
Speaker *Alarm::alarm_speaker = new Speaker(100.0f, true);

void Alarm::cleanup(){
	delete alarm_speaker;
}



Alarm::Alarm(jb::Time initTarget, std::string initMsg, bool initActive)
	: target(initTarget), msg(initMsg), active(initActive), alarm_name("tone1.wav")
{ 
}

Alarm::Alarm(const Alarm& other)
	: target(other.target), msg(other.msg), active(other.active), alarm_name(other.alarm_name)
{ 
}

Alarm::~Alarm(){
}



bool Alarm::operator<(const Alarm& other) const {
	return this->target < other.target;
}


void Alarm::query(jb::Time t){
	if (active && t == target){
		this->trigger();
	}
}

void Alarm::trigger(){
	std::cout << this->msg << std::endl;

	// sound the alarm if speaker is free
	if (! alarm_speaker->is_playing()){
		alarm_speaker->play(alarm_name);
	}
}


void Alarm::silence(){
	alarm_speaker->stop();
}




