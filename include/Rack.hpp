#pragma once
#include <jb.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>
#include <Entity.hpp>


class Rack {
public:
	static void cleanup();

	Rack(std::string _name);
	~Rack();
	void add_alarm(jb::Time target, std::string message);
	void query_active_alarms(const jb::Time t);
	void select_move(jb::Direc direction);
	void toggle_selection();
	void duplicate_alarm();
	void adjust_dup_increment(int value);
	void remove_alarm();
	void insert_alarm(Alarm newAlarm, bool audible = true);
	std::string get_selection_message();
	void edit_selection(std::string);

	inline void set_select(const int new_index){
		select_index = new_index;
		jb::clamp(select_index, 0, alarms.size());
	}

	inline int size(){
		return alarms.size();
	}

	static const int max_dup_increment;
	static Speaker *rack_speaker;

	int select_index, dup_increment;
	std::vector<Alarm> alarms;
	std::string name;



protected:
	 ThreadClock *clock;

};



