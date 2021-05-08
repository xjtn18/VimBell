#pragma once
#include <ctime>
#include <string>
#include <Debug.hpp>
#include <Sound.hpp>


namespace jb {

	typedef struct Time {
		int hour;
		int minute;

		Time()
			: hour(0), minute(0)
		{ }

		Time(int hr, int mn)
			: hour(hr), minute(mn)
		{ }

		bool operator ==(const Time& other) const { // equals operator
			return minute == other.minute && hour == other.hour;
		}

		Time(const Time& other) // copy constructor
			: hour(other.hour), minute(other.minute)
		{ }

		Time operator +(const int& increment) const {
			std::time_t sinceEpoch = std::time(nullptr);
			std::tm startT = *std::localtime(&sinceEpoch);
			startT.tm_hour = this->hour;
			startT.tm_min = this->minute;
			std::time_t t = std::mktime(&startT) + increment * 60;
			std::tm newT = *std::localtime(&t);
			return Time(newT.tm_hour, newT.tm_min);
		}

		friend std::ostream& operator <<(std::ostream& os, const Time& time){
			os << "Time(" << time.hour << "h, " << time.minute << "m)";
			return os;
		}
	} Time;



	extern const char* rootPath;
	const Time current_time();
	const char* rtrim(const char* s, size_t len, const char target);
	const char* getResource(const char* filename);

}


