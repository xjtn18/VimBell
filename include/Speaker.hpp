#pragma once
#include <SFML/Audio.hpp>
#include <jb.hpp>
#include <unordered_map>


namespace aud {
	
	extern std::unordered_map<std::string, sf::SoundBuffer> sound_map;
	void load_all();
	void cleanup();



	class Speaker {
		sf::SoundBuffer buffer;
		sf::Sound sound;

	public:

		Speaker() { };
		Speaker(const char* filename, float vol = 100.0f, bool loop = false);
		Speaker(float vol = 100.0f, bool loop = false);
		Speaker(const Speaker& from);
		Speaker& operator =(const Speaker& from);
		static void cleanup();
		~Speaker();

		void play(std::string sound_name);
		void stop();
		bool is_playing() const;

	};


};


