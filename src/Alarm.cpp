#include <Alarm.hpp>


/// statics
Speaker *Alarm::alarm_speaker = new Speaker(100.0f, true);

void Alarm::cleanup(){
	delete alarm_speaker;
}



Alarm::Alarm(jb::Time initTarget, std::string initMsg, bool initActive)
	: target(initTarget),
	msg(initMsg),
	active(initActive),
	alarm_name("meadows.wav"),
	stacc(1),
	stacc_interval(1)
{ 
}


Alarm::~Alarm(){
}



bool Alarm::operator<(const Alarm& other) const {
	return this->target < other.target;
}



void Alarm::add_to_stack(){
	jb::clamp(++stacc, 1, 11);
}



bool Alarm::remove_from_stack(){
	return jb::clamp(--stacc, 1, 11);
}



void Alarm::query(jb::Time t){
	if (active){
		for (int i = 0; i < stacc; ++i){
			if (target + stacc_interval * i == t){
				this->trigger();
			}
		}
	}
}

void Alarm::trigger(){
	// sound the alarm if speaker is free
	if (! alarm_speaker->is_playing()){
		alarm_speaker->play(alarm_name);
	}
}


void Alarm::silence(){
	alarm_speaker->stop();
}




