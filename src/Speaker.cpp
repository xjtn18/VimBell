#include <Speaker.hpp>
#include <vb.hpp>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace aud;


std::unordered_map<std::string, sf::SoundBuffer> aud::sound_map;


void aud::cleanup(){
	sound_map.clear(); // delete all the sound buffers we loaded
}


void aud::load_all(){
	// load all sounds found in res/sounds
	sf::SoundBuffer sbuf; 
	std::string filename;

	for (const auto& entry : fs::directory_iterator("res/sounds/")){
		filename = entry.path().filename().u8string();
		sbuf.loadFromFile("res/sounds/" + filename);
		sound_map[filename] = sbuf;
	}
}


Speaker::Speaker(const char* filename, float vol, bool loop){
	//buffer.loadFromFile(filename);
	//sound.setBuffer(buffer);
	sound.setVolume(vol);
	sound.setLoop(loop);
}

Speaker::Speaker(float vol, bool loop){
	sound.setVolume(vol);
	sound.setLoop(loop);
}

Speaker::Speaker(const Speaker& from)
//	: buffer(from.buffer)
{ }

Speaker& Speaker::operator=(const Speaker& from){
	if (this != &from){
		//buffer = from.buffer; // creates a COPY of the sound buffer
		//sound.setBuffer(buffer); // do not use from.buffer, use our copy
		sound.setVolume(from.sound.getVolume());
		sound.setLoop(from.sound.getLoop());
	}
	return *this;
}

Speaker::~Speaker(){
}


void Speaker::play(std::string sound_name){
	if (not_in(sound_name, sound_map)){
		std::cout << "Error: Unable to find sound named '" << sound_name << "' in sound map." << std::endl;
	}
	sound.setBuffer(sound_map.at(sound_name));
	sound.play();
}

void Speaker::stop(){
	sound.stop();
}

bool Speaker::is_playing() const {
	return sound.getStatus() == sf::SoundSource::Playing;
}



