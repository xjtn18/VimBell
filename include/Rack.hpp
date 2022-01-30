#pragma once
#include <vb.hpp>


// FD
namespace aud {
	struct Speaker;
}
struct ThreadClock;
struct Alarm;
struct Program;


struct Rack {
	static void cleanup();

	Rack(std::string _name, Program &p);
	Rack(const Rack&) = default;
	Rack& operator=(const Rack& other);
	~Rack();

	void add_alarm(vb::Time target, std::string message);
	std::vector<int> query_alarms(const vb::Time t);
	void select_move(vb::Direc direction);
	Alarm& get_selection();
	void toggle_selection();
	void remove_alarm();
	void insert_alarm(Alarm new_alarm, bool audible = true);
	std::string get_selection_message();
	void edit_selection(std::string);
	void set_select(const int new_index);
	int size();


	static aud::Speaker *rack_speaker;

	int select_index;
	std::vector<Alarm> alarms;
	std::string name;
	ThreadClock *clock;
};



