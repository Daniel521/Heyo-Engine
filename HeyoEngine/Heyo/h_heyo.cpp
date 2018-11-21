#include "h_heyo.h"	
//#include "..\SDL2\include\SDL.h"
//#include "..\SDL2\include\SDL_image.h"
//#include "..\SDL2\include\SDL_mixer.h"
//#include "..\SDL2\include\SDL_ttf.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Heyo {
	EngineClass * Engine = new EngineClass();

	bool initHeyo() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			SDL_Log("Failed to initiate video: %s\n", SDL_GetError());
			return false;
		}
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(IMG_INIT_PNG) & imgFlags)) {
			SDL_Log("Failed to initiate IMG: %s\n", IMG_GetError());
			return false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			SDL_Log("Failed to initiate Sound Mixer: %s\n", Mix_GetError());
			return false;
		}
		if (TTF_Init() == -1) {
			SDL_Log("Failed to initiate text: %s\n", TTF_GetError());
			return false;
		}
		return true;
	}

	void closeHeyo() {
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

}

int main(int argc, char * argv[]) { 
	Heyo::initHeyo();

	int returnValue = 1;
	returnValue = HeyoMain();
	
	Heyo::Engine->close();
	delete Heyo::Engine;

	Heyo::closeHeyo();
	return returnValue;
}

EngineClass::EngineClass() : graphics(NULL), sound(NULL), input(NULL), timer(NULL), music(NULL) {}

EngineClass::EngineClass(unsigned int width, unsigned int height, std::string title) {
	graphics = new Heyo::Graphics(width, height, title);
	sound = new Heyo::SoundPlayer();
	input = new Heyo::Events();
	timer = new Heyo::LTimer();
	music = new Heyo::Music();
}

EngineClass::~EngineClass() {
	close();
}

bool EngineClass::loop() {
	timer->getTicks();
	timer->start();

	return input->loop();
}

bool EngineClass::init(unsigned int width, unsigned int height, std::string title) {
	if (graphics != NULL)
		return false;

	graphics = new Heyo::Graphics(width, height, title);
	sound = new Heyo::SoundPlayer();
	input = new Heyo::Events();
	timer = new Heyo::LTimer();
	music = new Heyo::Music();

	return true;
}

void EngineClass::close() {
	if (graphics != NULL) {
		delete graphics;
		graphics = NULL;
	}

	if (sound != NULL) {
		delete sound;
		sound = NULL;
	}

	if (music != NULL) {
		delete music;
		music = NULL;
	}

	if (input != NULL) {
		delete input;
		input = NULL;
	}

	if (timer != NULL) {
		delete timer;
		timer = NULL;
	}
}