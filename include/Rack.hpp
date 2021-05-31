#pragma once
#include <jb.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>


class Rack {
public:
Rack();
	~Rack();
	void add_alarm(std::string message);
	void query_active_alarms(const jb::Time t);
	void select_move(jb::Direc direction);
	void toggle_selection();
	void duplicate_alarm();
	void set_dup_increment(int value);
	void adjust_dup_increment(int value);
	void remove_alarm();
	void insert_alarm(Alarm newAlarm);
	static void cleanup();

	inline const int& get_select_index(){
		return select_index;
	}
	inline const std::vector<Alarm>& get_alarms() const {
		return alarms;
	}

	inline int size() const {
		return alarms.size();
	}


private:
	int select_index, dup_increment;
	static const int max_dup_increment;
	std::vector<Alarm> alarms;
	static Speaker *rack_speaker;

protected:
	 ThreadClock *clock;

};



