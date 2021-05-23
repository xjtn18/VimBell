#include <Alarm.hpp>


/// statics
Sound* Alarm::global_alarm_speaker = new Sound(100.0f, true);

void Alarm::cleanup(){
	delete global_alarm_speaker;
}




Alarm::Alarm()
{ }

Alarm::Alarm(jb::Time initTarget, std::string initMsg, bool initActive)
	: target(initTarget), msg(initMsg), active(initActive), sound_name(jb::get_resource("sounds/tone1.wav"))
{ 
}

Alarm::Alarm(const Alarm& other)
	: target(other.target), msg(other.msg), active(other.active), sound_name(other.sound_name)
{ 
}

Alarm::~Alarm(){
}


void Alarm::query(jb::Time t){
	if (active && t == target){
		this->trigger();
	}
}

void Alarm::trigger(){
	std::cout << this->msg << std::endl;

	// sound the alarm if speaker is free
	if (! global_alarm_speaker->is_playing()){
		global_alarm_speaker->set_sound(sound_name);
		global_alarm_speaker->play();
	}
}


void Alarm::silence(){
	global_alarm_speaker->stop();
}




