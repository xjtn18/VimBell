#include <ThreadClock.hpp>
#include <Rack.hpp>
#include <Program.hpp>
#include <Menu.hpp>


ThreadClock::ThreadClock(std::shared_ptr<Rack> _rack, Program &p)
	: thr(std::thread(&ThreadClock::callback, this, std::ref(p))),
		stopped(false),
		rack(_rack)
{ }


void ThreadClock::stop(){
	stopped = true;
	thr.join();
}


void ThreadClock::callback(Program &p){
	vb::Time localTime;
	int minuteLoopRef = -1;

	while (! stopped){
		localTime = vb::current_time();
		if (localTime.minute != minuteLoopRef){
			std::vector<int> triggered = rack->query_alarms(localTime);
			if (triggered.size() != 0) p.rack_view->trigger(triggered);
			minuteLoopRef = localTime.minute;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}


