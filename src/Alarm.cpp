#include <Alarm.hpp>


Alarm::Alarm(jb::Time initTarget, std::string initMsg, bool initActive)
	: target(initTarget), msg(initMsg), active(initActive),
		snd(aud::Sound(jb::getResource("sounds/tone1.wav"), 100.0f, true))
{ }


void Alarm::query(jb::Time t){
	if (active && t == target){
		this->trigger();
	}
}

void Alarm::trigger(){
	std::cout << this->msg << std::endl;
	snd.play();
}



Alarm::~Alarm(){
}


