#include <Rack.hpp>




Rack::Rack() 
{ }

Rack::~Rack()
{ }


void Rack::add_alarm(){
	jb::Time target = jb::current_time() + 1;
	dlog(target);
	alarms.emplace_back(target, "Time for work!");
	std::cout << "There is now " << alarms.size() << " alarm[s] set.\n";
}


void Rack::query_active_alarms(const jb::Time t){
	for (Alarm& a : alarms){
		a.query(t);
	}
}



