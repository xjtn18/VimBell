#include <SaveLoad.hpp>
#include <jb.hpp>
#include <Rack.hpp>
#include <Alarm.hpp>

#include <fstream>

using namespace json;


#define JSON_GET_VAL(x,y,z) ((z)x[y]).Value()


void load_rack(std::shared_ptr<Rack> &rack, const std::string &rack_name){
	rack = std::shared_ptr<Rack>(new Rack(rack_name));

	std::fstream fs;
	fs.open("racks/" + rack_name + ".rack", std::fstream::in);
   Object objDocument;
   //const Object& objRoot = objDocument;
	try {
		Reader::Read(objDocument, fs);
	} catch (Reader::ScanException& e){
		fs.close();
		return; // nothing to load
	}
	fs.close();

	const Array& arrayAlarms = objDocument[rack_name];
   Array::const_iterator it(arrayAlarms.Begin()), itEnd(arrayAlarms.End());
   for (; it != itEnd; ++it){ // for each Alarm
		const Object& objAlarm = *it;

		std::string msg = JSON_GET_VAL(objAlarm, "Message", String);
		int hour = JSON_GET_VAL(objAlarm, "TargetHour", Number);
		int minute = JSON_GET_VAL(objAlarm, "TargetMinute", Number);
		int stacc = JSON_GET_VAL(objAlarm, "Stacc", Number);
		int interval = JSON_GET_VAL(objAlarm, "StaccInterval", Number);
		bool active = JSON_GET_VAL(objAlarm, "Active", Boolean);

		rack->insert_alarm(Alarm(jb::Time(hour, minute), msg, stacc, interval, active), false);
	}

	rack->set_select(0);
}



void save_rack(const std::shared_ptr<Rack>& rack){
   Array arrayAlarms;
	std::vector<Alarm> alarms = rack->alarms;

	for (auto& a : alarms){
		Object objAlarm;
		objAlarm["Message"] = String(a.msg);
		objAlarm["TargetHour"] = Number(a.target.hour);
		objAlarm["TargetMinute"] = Number(a.target.minute);
		objAlarm["Stacc"] = Number(a.stacc);
		objAlarm["StaccInterval"] = Number(a.stacc_interval);
		objAlarm["Active"] = Boolean(a.active);
		arrayAlarms.Insert(objAlarm);
	}

   Object objDocument;
   objDocument[rack->name] = arrayAlarms;
	std::fstream fs;
	fs.open("racks/" + rack->name + ".rack", std::fstream::out);
	Writer::Write(objDocument, fs);
	fs.close();
}



