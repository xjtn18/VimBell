#include <Rack.hpp>


Rack::Rack() 
	: select_index(0)
{ 
	clock = new ThreadClock(std::shared_ptr<Rack>(this)); // run clock checking thread
}


Rack::~Rack()
{ 
	if (clock != nullptr){
		clock->stop();
	}
}


void Rack::add_alarm(std::string message){
	jb::Time target = jb::current_time() + 1;
	insert_alarm(Alarm(target, message, false));
}


void Rack::query_active_alarms(const jb::Time t){
	for (Alarm& a : alarms){
		a.query(t);
	}
}


void Rack::select_move(jb::Direc direction){
	int _tmp = select_index;
	select_index += direction;
	jb::clamp(select_index, 0, alarms.size());

	if (alarms.size() > 0){
		if (_tmp != select_index){
			Sound::move_sound->play();
		} else { // tried to move past boundary
			Sound::err_sound->play();
		}
	} else {
		//Sound::empty_move_sound->play();
	}
}


void Rack::toggle_selection(){
	if (alarms.size() > 0){
		alarms[select_index].toggle();
		Sound::press_sound->play();
	}
}


void Rack::duplicate_alarm(){
	if (alarms.size() == 0){
		add_alarm("placeholder");
	} else {
		Alarm& curr = alarms[select_index]; // currently selected alarm
		Alarm dup = Alarm(curr);
		dup.set_target(curr.get_target() + 1);
		insert_alarm(dup);
	}
}


void Rack::remove_alarm(){
	if (alarms.size() > 0){
		Sound::remove_sound->play();
		alarms.erase(alarms.begin() + select_index); // remove alarm from list
		if (select_index == alarms.size()){ 			// transition selector correctly
			// if the selector index is out of bounds, decrement it.
			select_index--;
			jb::clamp(select_index, 0, alarms.size());
		}
	}
}


void Rack::insert_alarm(Alarm newAlarm){
	Sound::create_sound->play();
	if (alarms.size() != 0){
		alarms.insert(alarms.begin() + select_index + 1, newAlarm);
	} else {
		alarms.push_back(newAlarm);
	}
	select_index += 1;
	jb::clamp(select_index, 0, alarms.size());
}



void Rack::quiet(){
	Alarm::silence();
	// Below is where we could remove any info about previously triggered alarms
	/*
	for (Alarm& a : alarms){
		a.hide_something();
	}
	*/
}


