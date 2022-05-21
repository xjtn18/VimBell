#include <Rack.hpp>
#include <Speaker.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>
#include <Menu.hpp>
#include <Program.hpp>


aud::Speaker *Rack::rack_speaker = new aud::Speaker(100.0f, false);

void Rack::cleanup(){
	delete rack_speaker;
}



Rack::Rack(std::string _name, Program &p)
	: name(_name),
	  select_index(0)
{
	clock = new ThreadClock(std::shared_ptr<Rack>(this), p); // run clock thread
}


Rack& Rack::operator=(const Rack& other){
	if (&other != this){
		name = other.name;
		select_index = other.select_index;
	}
	return *this;
}


Rack::~Rack()
{ 
	if (clock != nullptr){
		clock->stop();
	}
}



Alarm& Rack::get_selection(){
	return alarms[select_index];
}


int Rack::size(){
	return alarms.size();
}

bool Rack::is_full(){
	return this->size() == Rack::max_capacity;
}


void Rack::add_alarm(vb::Time target, std::string message){
	insert_alarm(Alarm(target, message, 1, 1, true));
}


void Rack::insert_alarm(Alarm new_alarm, bool audible){
	if (audible) rack_speaker->play("create.wav");

	if (!this->is_full()){
		auto lower = std::lower_bound(alarms.begin(), alarms.end(), new_alarm);
		select_index = std::distance(alarms.begin(), lower); // std::distance helps us convert iterator to integer index; set the index to the newly added alarm
		alarms.insert(lower, new_alarm);
	} else { // rack is full
		rack_speaker->play("error.wav");
	}
}



std::vector<int> Rack::query_alarms(const vb::Time t){
	std::vector<int> triggered;
	for (int i = 0; i < alarms.size(); ++i){
		if (alarms[i].query(t)){ // alarm was triggered
			triggered.push_back(i);
		}
	}
	return triggered;
}



void Rack::select_move(vb::Direc direction){
	select_index += direction;
	bool clamped = vb::clamp(select_index, 0, alarms.size());
}

void Rack::set_select(const int new_index){
	select_index = new_index;
	vb::clamp(select_index, 0, alarms.size());
}


void Rack::toggle_selection(){
	if (alarms.size() > 0){
		alarms[select_index].toggle();
		rack_speaker->play("click.wav");
	}
}


void Rack::remove_alarm(){
	if (alarms.size() > 0){
		rack_speaker->play("remove.wav");
		alarms.erase(alarms.begin() + select_index); // remove alarm from list
		if (select_index == alarms.size()){ 			// transition selector correctly
			// if the selector index is out of bounds, decrement it.
			select_index--;
			vb::clamp(select_index, 0, alarms.size());
		}
	}
}



std::string Rack::get_selection_message(){
	return alarms[select_index].msg;
}

void Rack::edit_selection(vb::Time new_target, std::string new_message){
	alarms[select_index].msg = new_message;
	alarms[select_index].target = new_target;
}



