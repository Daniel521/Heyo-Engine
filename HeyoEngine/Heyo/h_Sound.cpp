#include "h_Sound.h"
//#include "..\SDL2\include\SDL.h"
#include <SDL.h>
#include <string>

#include <iostream>
using namespace std;

namespace Heyo {

	Music::Music() : m_music(NULL), m_volume(100)
	{
	}

	Music::~Music()
	{
		if (m_music != NULL)
			Mix_FreeMusic(m_music);
	}

	bool Music::loadMusic(std::string musicAddress)
	{
		if (m_music != NULL)
			Mix_FreeMusic(m_music);
		m_music = Mix_LoadMUS(musicAddress.c_str());
		if (m_music == NULL)
		{
			SDL_Log("Failed to load %s.\n", musicAddress);
			return false;
		}
		return true;
	}

	bool Music::playing()
	{
		return Mix_PlayingMusic();
	}

	void Music::stop(int ms)
	{
		Mix_FadeOutMusic(ms);
	}

	void Music::setVolume(Uint8 volume)
	{
		volume = (volume * 128) / 100;
		m_volume = volume;
		Mix_VolumeMusic(volume);
	}

	void Music::play()
	{
		Mix_PlayMusic(m_music, 0);
	}

	SoundPlayer::SoundPlayer() : CHANNELS_PER_SOUNDEFFECT(M_SE), m_Max_Volume(100)
	{
		Mix_AllocateChannels(64);
	}

	SoundPlayer::SoundPlayer(int chans_per_soundeffect) : CHANNELS_PER_SOUNDEFFECT(chans_per_soundeffect), m_Max_Volume(100)
	{
		Mix_AllocateChannels(64);
	}

	SoundPlayer::~SoundPlayer()
	{
		for (vector<SoundEffect>::iterator i = sounds.begin(); i != sounds.end(); i++)
		{
			i->clear();
		}
		sounds.clear();
	}

	void SoundPlayer::clear()
	{
		for (vector<SoundEffect>::iterator i = sounds.begin(); i != sounds.end(); i++)
		{
			i->clear();
		}
		sounds.clear();
	}

	void SoundPlayer::pop_back()
	{
		Mix_HaltGroup(static_cast<int>(sounds.size()) - 1);
		sounds.rbegin()->clear();
		sounds.pop_back();
	}

	int SoundPlayer::addSoundEffect(string address)
	{
		int group = static_cast<int>(sounds.size());
		int first = group*CHANNELS_PER_SOUNDEFFECT;

		Mix_GroupChannels(first, first + CHANNELS_PER_SOUNDEFFECT - 1, group);

		SoundEffect temp(address, group, CHANNELS_PER_SOUNDEFFECT, first, first + CHANNELS_PER_SOUNDEFFECT - 1, m_Max_Volume);
		sounds.push_back(temp);
		sounds[group].init();

		return group;
	}

	bool SoundPlayer::play(int soundeffect_num, int volume, int fadein_ms)
	{
		if (soundeffect_num < 0 || soundeffect_num >= sounds.size())
		{
			SDL_Log("Playing a soundeffect that is not added.");
			return false;
		}

		sounds[soundeffect_num].play(volume, fadein_ms);
		return true;
	}

	void SoundPlayer::stop(int soundeffect_num, int ms)
	{
		if (soundeffect_num == -1)
		{
			Mix_FadeOutChannel(-1, ms);
		}
		else
			Mix_FadeOutGroup(soundeffect_num, ms);
	}

	int SoundPlayer::getSoundEffect(string address)
	{
		for (vector<SoundEffect>::iterator i = sounds.begin(); i != sounds.end(); i++)
		{
			if (i->getAddress() == address)
			{
				return i->getGroup();
			}
		}
		return -1;
	}

	void SoundPlayer::setMax_Volume(int vol)
	{
		for (vector<SoundEffect>::iterator i = sounds.begin(); i != sounds.end(); i++)
		{
			i->setMax_Volume(vol);
		}
		//music.setVolume(vol);
	}


	SoundEffect::SoundEffect(string address, int group, int m_c, int first, int last, int Max_Volume) : MAX_CHANNELS(m_c), FIRSTCHAN(first), LASTCHAN(last), GROUP(group), m_chunk(NULL), m_nextChan(FIRSTCHAN), m_address(address), m_Max_Volume(Max_Volume)
	{

	}

	SoundEffect::~SoundEffect()
	{
	}

	void SoundEffect::init()
	{
		m_chunk = Mix_LoadWAV(m_address.c_str());
		if (m_chunk == NULL)
		{
			SDL_Log("Failed to load %s.\n", m_address);
		}
	}

	void SoundEffect::clear()
	{
		if (m_chunk != NULL)
			Mix_FreeChunk(m_chunk);
	}

	void SoundEffect::play(int volume, int ms)
	{
		volume = static_cast<int>((volume * m_Max_Volume * 128.0) / 10000) ;
		Mix_Volume(m_nextChan, volume);

		m_nextChan = Mix_FadeInChannel(m_nextChan, m_chunk, 0, ms);

		if (m_nextChan >= LASTCHAN)
			m_nextChan = FIRSTCHAN;
		else
			m_nextChan++;
	}

	//void SoundEffect::playFadeOut(int volume, int ms)
	//{
	//	Mix_PlayChannel(m_nextChan, m_chunk, 0);
	//	SDL_Log("Channel : %s", m_nextChan);

	//	volume = (volume / 100.0) * 128;
	//	Mix_Volume(m_nextChan, volume);

	//	Mix_FadeOutChannel(m_nextChan, ms);

	//	if (m_nextChan >= LASTCHAN)
	//		m_nextChan = FIRSTCHAN;
	//	else
	//		m_nextChan++;
	//}

}