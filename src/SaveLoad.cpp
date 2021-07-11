#include <SaveLoad.hpp>
using namespace json;


void load_rack(std::shared_ptr<Rack>& rack, const std::string& rack_name){
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

		// get the alarm target time
		const Number& hour = objAlarm["TargetHour"];
		const Number& minute = objAlarm["TargetMinute"];
		jb::Time t = {(int) hour.Value(), (int) minute.Value()};

		// get the alarm message
		const String& objMessage = objAlarm["Message"];
		std::string msg = objMessage.Value();

		// get the active state
		const Boolean& objActive = objAlarm["Active"];
		bool active = objActive.Value();

		rack->insert_alarm(Alarm(t, msg, active), false);
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
		objAlarm["Active"] = Boolean(a.active);
		arrayAlarms.Insert(objAlarm);
	}


   Object objDocument;
   objDocument[rack->name] = arrayAlarms;
	std::fstream fs;
	fs.open("racks" + rack->name + ".rack", std::fstream::out);
	Writer::Write(objDocument, fs);
	fs.close();
}



