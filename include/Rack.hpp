#pragma once
#include <jb.hpp>
#include <Alarm.hpp>
#include <ThreadClock.hpp>


class Rack {
public:

	Rack();
	~Rack();
	void add_alarm();
	void query_active_alarms(const jb::Time t);
	void select_move(jb::Direc direction);
	void insert_alarm();
	void toggle_selection();
	void duplicate_alarm();
	void insert_alarm(Alarm newAlarm);
	void quiet();
	const int& get_select_index();
	const std::vector<Alarm>& get_alarms() const;

	inline int get_size() const {
		return alarms.size();
	}


private:
	int select_index;
	std::vector<Alarm> alarms;

protected:
	 ThreadClock* clock;

};



