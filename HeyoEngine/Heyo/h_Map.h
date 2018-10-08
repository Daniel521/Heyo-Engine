#pragma once
/**************************
//		Map Class
//	This  class is used to make platform maps.
**************************/
#include "h_Sprite.h"
#include "h_Character.h"
#include <vector>


namespace Heyo_Platform
{
	class Map
	{
	public:
	// Private variables --- Public for now...	1/13/18

		Heyo_Platform::Character * main_character;
		int sensor_width;
		Heyo::Rect sensor_rect;

		Heyo::Sprite * background;
		Heyo::Rect rect_background;
		Heyo::Sprite * mainground;
		Heyo::Rect rect_mainground;

		std::vector<Heyo::Rect> coll_rect;

	public:
		// Main functions
		Map();
		~Map();

		// This function will specify who the main character is
		// and who the camera will follow
		// sensor_width: the width of the area the character can wonder in
		bool loadMainCharacter(Character & main_character, int sensor_width = 0);

		// Specify the address of the background
		bool loadBackground(std::string address);
		// To be added later... allow the user to just specify a color and use that as the background
		//bool setBackground(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0);

		bool loadCollision(std::string address);

		// Specify the mainground addres,
		// width and height specifies how many pixels the mainground is
		// leave as -1 to leave as screen size;
		bool loadMainground(std::string address, int width = -1, int height = -1);

		void update();

		void draw(bool drawSensor = false);

	public:
		// Get and Set Functions
		void setMaingoundHeight(int height);
		void setMaingroundWidth(int width);

		int getMaingroundHeight();
		int getMaingroundWidth();
	};

	class Collider
	{

	};

}