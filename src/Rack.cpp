#include <Rack.hpp>

Speaker *Rack::rack_speaker			 = new Speaker(100.0f, false);
const int Rack::max_dup_increment	 = 121; // upper bound, exclusive

void Rack::cleanup(){
	delete rack_speaker;
}



Rack::Rack(std::string _name)
	: name(_name),
	  select_index(0),
	  dup_increment(5)
{ 
	clock = new ThreadClock(std::shared_ptr<Rack>(this)); // run clock thread
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
	select_index += direction;
	bool clamped = jb::clamp(select_index, 0, alarms.size());

	if (alarms.size() > 0){
		if (!clamped){
			//rack_speaker->play("move.wav");
		} else { // tried to move past boundary
			rack_speaker->play("error.wav");
		}
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
		dup.target = curr.target + dup_increment;
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


void Rack::insert_alarm(Alarm newAlarm, bool audible){
	if (audible) rack_speaker->play("create.wav");
	if (alarms.size() != 0){
		alarms.insert(alarms.begin() + select_index + 1, newAlarm);
	} else {
		alarms.push_back(newAlarm);
	}
	select_index += 1;
	jb::clamp(select_index, 0, alarms.size());
}


void Rack::adjust_dup_increment(int value){
	dup_increment += value;
	jb::clamp(dup_increment, 5, max_dup_increment);
}

std::string Rack::get_selection_message(){
	return alarms[select_index].msg;
}

void Rack::edit_selection(std::string new_message){
	alarms[select_index].msg = new_message;
}


