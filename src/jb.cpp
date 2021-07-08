#include <jb.hpp>
#include <stdarg.h>


const jb::Transform jb::Transform::Zero = {0,0,0,0};
const char* jb::rootPath = nullptr;


sf::Font INCON_FONT;

void load_font() {
	INCON_FONT.loadFromFile("res/fonts/incon.ttf");
}



const jb::Time jb::current_time(){
	std::time_t sinceEpoch = std::time(nullptr);
	std::tm t = *std::localtime(&sinceEpoch);
	return jb::Time(t.tm_hour, t.tm_min);
}


// takes path string literal and returns it sans tail
const char* jb::rtrim(const char* s, size_t len, const char target){
	size_t i = len-1;
	for (; i >= 0; i--){
		if (s[i] == target){ break; }
	}
	if (i < 0){ // tail is entire path
		return s;
	}
	char* res = new char[i+1];
	strncpy(res, s, i);
	res[i] = '\0';
	return res;
}


const char* jb::get_resource(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/");
	std::strcat(pth, filename);
	return pth;
}


const char* jb::get_image(const char* filename){
	char* pth = new char[100];
	std::strcpy(pth, jb::rootPath);
	std::strcat(pth, "/res/images/");
	std::strcat(pth, filename);
	return pth;
}





