#include <Alarm.hpp>
#include <Speaker.hpp>


/// statics
auto *Alarm::alarm_speaker = new aud::Speaker(100.0f, true);

void Alarm::cleanup(){
	delete alarm_speaker;
}



Alarm::Alarm(jb::Time initTarget, std::string initMsg, int initStacc, int initStaccInterval, bool initActive)
	: target(initTarget),
	msg(initMsg),
	active(initActive),
	alarm_name("tone1.wav"),
	stacc(initStacc),
	stacc_interval(initStaccInterval)
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


void Alarm::alter_stacc_interval(int i){
	stacc_interval += 5 * i;
	stacc_interval -= stacc_interval % 5;
	jb::clamp(stacc_interval, 1, 121);
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




