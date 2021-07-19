#pragma once
#include <jb.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>
#include <Entity.hpp>


struct Rack {
	static void cleanup();

	Rack(std::string _name);
	Rack(const Rack&) = default;
	Rack& operator=(const Rack& other);
	~Rack();

	void add_alarm(jb::Time target, std::string message);
	void query_active_alarms(const jb::Time t);
	void select_move(jb::Direc direction);
	void toggle_selection();
	void add_to_stack();
	void adjust_dup_increment(int value);
	bool remove_from_stack();
	void remove_alarm();
	void insert_alarm(Alarm new_alarm, bool audible = true);
	std::string get_selection_message();
	void edit_selection(std::string);

	inline void set_select(const int new_index){
		select_index = new_index;
		jb::clamp(select_index, 0, alarms.size());
	}

	inline int size(){
		return alarms.size();
	}

	static Speaker *rack_speaker;

	int select_index;
	std::vector<Alarm> alarms;
	std::string name;
	ThreadClock *clock;
};



