#pragma once
#include <SFML/Audio.hpp>
#include <jb.hpp>


namespace aud {
	
	class Sound; // FD
	#define UPS(x) std::unique_ptr<Sound>(new Sound(x))


	class Sound {
		sf::SoundBuffer buffer;
		sf::Sound sound;

	public:
		static std::unique_ptr<Sound> press_sound, err_sound, create_sound, move_sound, remove_sound;

		Sound() { };
		Sound(const char* filename, float vol = 100.0f, bool loop = false);
		Sound(float vol = 100.0f, bool loop = false);
		Sound(const Sound& from);
		Sound& operator =(const Sound& from);
		static void cleanup();
		~Sound();

		void set_sound(std::string sound_name);
		void play();
		void stop();
		bool is_playing() const;

	};


};


