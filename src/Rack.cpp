#include <Rack.hpp>


std::shared_ptr<Rack> Rack::currentRack = nullptr;


Rack::Rack() 
{ }

Rack::~Rack()
{ }


void Rack::add_alarm(){
	jb::Time target = jb::current_time();
	dlog(target);
	alarms.emplace_back(target, "Time for work!");
	std::cout << "There are now " << alarms.size() << " alarms set.\n";
}


void Rack::query_active_alarms(const jb::Time t){
	for (Alarm& a : alarms){
		a.query(t);
	}
}

void Rack::cleanup(){
	currentRack.reset();
}


