#pragma once

#include <utility>



struct Flag {
private:
	bool state;


public:

	Flag();
	void set();

	// Set 'state' to false and return its original value.
	explicit operator bool(){
		return std::exchange(state, false); 
	}

};