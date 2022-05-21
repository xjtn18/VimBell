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
	static const int max_capacity = 17;

	Rack(std::string, Program&);
	Rack(const Rack&) = default;
	Rack& operator=(const Rack& other);
	~Rack();

	void add_alarm(vb::Time, std::string);
	std::vector<int> query_alarms(const vb::Time);
	void select_move(vb::Direc);
	Alarm& get_selection();
	void toggle_selection();
	void remove_alarm();
	void insert_alarm(Alarm, bool = true);
	std::string get_selection_message();
	void edit_selection(vb::Time, std::string);
	void set_select(const int);
	int size();
	bool is_full();


	static aud::Speaker *rack_speaker;

	int select_index;
	std::vector<Alarm> alarms;
	std::string name;
	ThreadClock *clock;
};



