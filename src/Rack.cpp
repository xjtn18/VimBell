#include <Rack.hpp>

Speaker *Rack::rack_speaker 			= new Speaker(100.0f, false);
const int Rack::max_dup_increment 	= 120;


Rack::Rack() 
	: select_index(0), dup_increment(5)
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
	insert_alarm(Alarm(target, message));
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
			rack_speaker->play("move.wav");
		} else { // tried to move past boundary
			rack_speaker->play("error.wav");
		}
	} else {
		//Sound::empty_move_sound->play();
	}
}


void Rack::toggle_selection(){
	if (alarms.size() > 0){
		alarms[select_index].toggle();
		rack_speaker->play("click.wav");
	}
}


void Rack::duplicate_alarm(){
	if (alarms.size() == 0){
		add_alarm("---"); // THIS SHOULD NEVER HAPPEN!
	} else {
		Alarm& curr = alarms[select_index]; // currently selected alarm
		Alarm dup = Alarm(curr);
		dup.set_target(curr.get_target() + dup_increment);
		insert_alarm(dup);
	}
}


void Rack::remove_alarm(){
	if (alarms.size() > 0){
		rack_speaker->play("remove.wav");
		alarms.erase(alarms.begin() + select_index); // remove alarm from list
		if (select_index == alarms.size()){ 			// transition selector correctly
			// if the selector index is out of bounds, decrement it.
			select_index--;
			jb::clamp(select_index, 0, alarms.size());
		}
	}
}


void Rack::insert_alarm(Alarm newAlarm){
	rack_speaker->play("create.wav");
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
}

void Rack::cleanup(){
	delete rack_speaker;
}


void Rack::set_dup_increment(int value){
	dup_increment = value;
}

void Rack::adjust_dup_increment(int value){
	dup_increment += value;
	jb::clamp(dup_increment, 5, max_dup_increment);
}




