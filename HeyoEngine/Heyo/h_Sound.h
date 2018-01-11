#pragma once
//#include "..\SDL2\include\SDL_mixer.h"
#include <SDL_mixer.h>
#include <vector>
#include <string>

using std::string;

#define M_SE 4

namespace Heyo {
	class SoundEffect {
	private:
		int MAX_CHANNELS;
		int FIRSTCHAN;
		int LASTCHAN;
		int GROUP;
		Mix_Chunk * m_chunk;
		string m_address;
		int m_Max_Volume;

		int m_nextChan;

	public:
		SoundEffect(std::string address, int group, int m_c, int first, int last, int Max_Volume);
		~SoundEffect();

		void init();
		void clear();

		// play a sound
		// ms : ms to fade in
		void play(int volume = 100, int ms = 0);

		// play a sound
		// ms : ms to fade out after starting
		//void playFadeOut(int volume = 100, int ms = 0); // 11/20/17 : Temporarly removed, scared it may not work

		// stop all songs in the group
		// ms : ms to fade out
		//void stop(int ms);

		int getFirstChan()	{ return FIRSTCHAN; }
		int getLastChan()	{ return LASTCHAN; }
		int getGroup()		{ return GROUP; }
		string getAddress() { return m_address; }

		void setMax_Volume(int vol) { m_Max_Volume = vol; }


		friend class SoundPlayer;
	};


	class Music
	{
	private:
		Mix_Music * m_music;
		Uint8 m_volume;

	public:
		Music();
		~Music();

		bool loadMusic(std::string musicAddress);

		bool playing();

		void stop(int ms = 0);

		// Sets music's volume
		// From a value of 0-100,
		// default value is 100
		void setVolume(Uint8 volume = 100);

		void play();

		void pause() { Mix_PauseMusic(); }

		void resume() { Mix_ResumeMusic(); }

		// Returns volume
		Uint8 getVolume() { return m_volume; }
	};


	class SoundPlayer {
	private:

		const int CHANNELS_PER_SOUNDEFFECT;
		std::vector<SoundEffect> sounds;
		int m_Max_Volume;


	public:
		SoundPlayer();
		SoundPlayer( int chans_per_soundeffect);
		~SoundPlayer();

		// clears up all the sound effects stored in the vector
		void clear();


		void pop_back();

		int addSoundEffect(string address);

		// play sound, make sure it's defined first
		// soundeffect_num is the number of the soundeffect, it's returned by addSoundEffect, do not lose this number
		// volume : volume, 100 is max
		// fadein_ms : ms to fade in
		bool play(int soundeffect_num, int volume = 100, int fadein_ms = 0);
		
		// soundeffect_num == -1, then fade out all channels
		void stop(int soundeffect_num = -1, int ms = 0);
		int getnumSoundEffects() { return static_cast<int>(sounds.size()); }

		// get the sound effect number,
		// address : pass in the address of the soundeffect
		// returns -1 if cannot find it
		// WARNING::: if you have more than one soundeffect of the same file, this function will return the first soundeffect it finds with that address
		int getSoundEffect(string address);


		// for later, add a setmaxVolume();
		void setMax_Volume(int vol);

		int getMax_Volume() { return m_Max_Volume; }

	};

}