#include <ThreadClock.hpp>


ThreadClock::ThreadClock(std::shared_ptr<Rack> _rack)
	: thr(std::thread(&ThreadClock::callback, this)), rack(_rack)
{ }


void ThreadClock::stop(){
	stopped = true;
	thr.join();
}

void ThreadClock::callback(){
	jb::Time localTime;
	int minuteLoopRef = -1;

	while (! stopped){
		localTime = jb::current_time();
		if (localTime.minute != minuteLoopRef){
			rack->query_active_alarms(localTime);
			minuteLoopRef = localTime.minute;
		}
		sf::sleep(sf::milliseconds(500));
	}
}


