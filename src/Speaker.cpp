#include <Speaker.hpp>
using namespace aud;


//auto aud::sound_map = std::unordered_map<std::string, sf::SoundBuffer>;
std::unordered_map<std::string, sf::SoundBuffer> aud::sound_map;


void aud::cleanup(){
	sound_map.clear();
}


void aud::load_all(){
	// add new sounds here when they are added to resources dir
	std::string sound_names[] = 
		{ 	"error.wav",
			"create.wav", 
			"move.wav", 
			"remove.wav",
			"click.wav",
			"tone1.wav"
		};

	sf::SoundBuffer sbuf; 
	for (int i = 0; i < sizeof(sound_names)/sizeof(sound_names[0]); ++i){
		sbuf.loadFromFile("res/sounds/" + sound_names[i]);
		sound_map[sound_names[i]] = sbuf;
	}
}


Speaker::Speaker(const char* filename, float vol, bool loop){
	buffer.loadFromFile(filename);
	sound.setBuffer(buffer);
	sound.setVolume(vol);
	sound.setLoop(loop);
}

Speaker::Speaker(float vol, bool loop){
	sound.setVolume(vol);
	sound.setLoop(loop);
}

Speaker::Speaker(const Speaker& from)
	: buffer(from.buffer)
{ }

Speaker& Speaker::operator=(const Speaker& from){
	if (this != &from){
		buffer = from.buffer; // creates a COPY of the sound buffer
		sound.setBuffer(buffer); // do not use from.buffer, use our copy
		sound.setVolume(from.sound.getVolume());
		sound.setLoop(from.sound.getLoop());
	}
	return *this;
}

Speaker::~Speaker(){
}


void Speaker::play(std::string sound_name){
	sound.setBuffer(sound_map[sound_name]);
	sound.play();
}

void Speaker::stop(){
	sound.stop();
}

bool Speaker::is_playing() const {
	return sound.getStatus() == sf::SoundSource::Playing;
}




