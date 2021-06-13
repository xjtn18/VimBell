#pragma once
#include <jb.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>


class Rack {
public:
	static void cleanup();

	Rack(std::string _name);
	~Rack();
	void add_alarm(std::string message);
	void query_active_alarms(const jb::Time t);
	void select_move(jb::Direc direction);
	void toggle_selection();
	void duplicate_alarm();
	void set_dup_increment(int value);
	void adjust_dup_increment(int value);
	void remove_alarm();
	void insert_alarm(Alarm newAlarm, bool audible = true);
	std::string get_selection_message();
	void edit_selection(std::string);

	inline const int& get_select_index(){
		return select_index;
	}

	inline const std::vector<Alarm>& get_alarms() const {
		return alarms;
	}

	inline void set_select(size_t index){
		select_index = index;
	}

	inline size_t size() const {
		return alarms.size();
	}

	inline std::string get_name() const {
		return name;
	}


private:
	static const int max_dup_increment;
	static Speaker *rack_speaker;

	int select_index, dup_increment;
	std::vector<Alarm> alarms;
	std::string name;

protected:
	 ThreadClock *clock;

};



