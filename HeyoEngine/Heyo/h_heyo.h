#pragma once

#include <string>
//#include <map>
#include "h_Graphics.h"
#include "h_Sprite.h"
#include "h_Text.h"
#include "h_Sound.h"
#include "h_Event.h"
#include "h_LTimer.h"

int HeyoMain();

class EngineClass {
public:
	Heyo::Graphics * graphics;
	//std::map<std::string, Heyo::Sprite> sprites;
	//std::map<std::string, Heyo::Sprite> texts;
	Heyo::SoundPlayer * sound;
	Heyo::Music * music;
	Heyo::Events * input;
	Heyo::LTimer * timer;

	EngineClass();
	EngineClass(unsigned int width, unsigned int height, std::string title);
	~EngineClass();

	bool loop();
	bool init(unsigned int width, unsigned int height, std::string title, bool fullscreen = false);
	void close();
	//void addSprite(string title, string imgaddress, int indiWidth = -1, int indiHeight = -1);
};

namespace Heyo {
	extern EngineClass * Engine;
	void closeHeyo();
	bool initHeyo();
}