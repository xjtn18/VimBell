#include <Rack.hpp>



Rack::Rack() 
	: select_index(0)
{ 
	clock = new ThreadClock(std::shared_ptr<Rack>(this));
}


Rack::~Rack()
{ 
	if (clock != nullptr){
		clock->stop();
	}
}


void Rack::add_alarm(){
	Sound::create_sound->play();
	jb::Time target = jb::current_time() + 1;
	dlog(target);
	alarms.emplace_back(Alarm(target, "Time for work!", false));
	std::cout << "There is now " << alarms.size() << " alarm[s] set.\n";
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

	if (_tmp != select_index){
		Sound::press_sound->play();
	} else { // tried to move past boundary
		Sound::err_sound->play();
	}
}


void Rack::toggle_selection(){
	alarms[select_index].toggle();
}


void Rack::duplicate_alarm(){
	Sound::create_sound->play();
	if (alarms.size() == 0){
		add_alarm();
	} else {
		Alarm& curr = alarms[select_index]; // currently selected alarm
		insert_alarm(Alarm(curr)); // insert a copy of the current alarm
		// move selector to the newly created alarm (dont call select move, we dont want move sound to trigger)
		select_index += jb::DOWN;
		jb::clamp(select_index, 0, alarms.size());
	}
}

void Rack::insert_alarm(Alarm newAlarm){
	alarms.insert(alarms.begin() + select_index + 1, newAlarm);
}

const std::vector<Alarm>& Rack::get_alarms() const {
	return alarms;
}

const int& Rack::get_select_index(){
	return select_index;
}

void Rack::quiet(){
	for (Alarm& a : alarms){
		a.silence();
	}
}




