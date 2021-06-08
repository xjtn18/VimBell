#include <SaveLoad.hpp>
using namespace json;


void load_rack(std::shared_ptr<Rack>& rack){
	rack = std::shared_ptr<Rack>(new Rack);

	std::fstream fs;
	fs.open("R1.rack", std::fstream::in);
   Object objDocument;
   //const Object& objRoot = objDocument;
	try {
		Reader::Read(objDocument, fs);
	} catch (Reader::ScanException& e){
		fs.close();
		return; // nothing to load
	}
	fs.close();

	const Array& arrayAlarms = objDocument["R1"];
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
	std::vector<Alarm> alarms = rack->get_alarms();

	for (auto& a : alarms){
		Object objAlarm;
		objAlarm["Message"] = String(a.get_msg());
		objAlarm["TargetHour"] = Number(a.get_target().hour);
		objAlarm["TargetMinute"] = Number(a.get_target().minute);
		objAlarm["Active"] = Boolean(a.is_active());
		arrayAlarms.Insert(objAlarm);
	}

	std::string rack_name = rack->get_name();

   Object objDocument;
   objDocument[rack_name] = arrayAlarms;
	std::fstream fs;
	fs.open(rack_name + ".rack", std::fstream::out);
	Writer::Write(objDocument, fs);
	fs.close();
}



