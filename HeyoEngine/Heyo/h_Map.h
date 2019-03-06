#pragma once
/**************************
//		Map Class
//	This  class is used to make platform maps.
**************************/
#include "h_Sprite.h"
#include "h_Character.h"
#include "h_heyo.h"
#include <vector>


//namespace Heyo_Platform
//{
//	class Map
//	{
//	public:
//	// Private variables --- Public for now...	1/13/18
//
//		Heyo_Platform::Character * main_character; // Maincharacter class
//		Heyo::Point point_main_character;	// Point to draw the main character, with respect to the windwo
//		Heyo::Point point_prev_main_xy; // the previous x & y value of main_character, e.g: main_character->getX()
//		int sensor_width;	// The width of the region the player can be, respect to the window
//		Heyo::Rect sensor_rect; // The rect of the region the player can be, respect to the window
//
//		Heyo::Sprite * background;
//		Heyo::Rect rect_background;
//		Heyo::Sprite * mainground;
//		Heyo::Rect rect_mainground;
//
//		std::vector<Heyo::Rect> coll_rect;
//
//		Heyo::Rect rect_map;
//		int x_offset;
//
//	public:
//		// Main functions
//		Map();
//		~Map();
//
//		// This function will specify who the main character is
//		// and who the camera will follow
//		// sensor_width: the width of the area the character can wonder in
//		bool loadMainCharacter(Character & main_character, unsigned int sensor_width = 100);
//
//		// Specify the address of the background
//		bool loadBackground(std::string address);
//		// To be added later... allow the user to just specify a color and use that as the background
//		//bool setBackground(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0);
//
//		bool loadCollision(std::string address);
//
//		// Specify the mainground addres,
//		// width and height specifies how many pixels the mainground is
//		// leave as -1 to leave as screen size;
//		bool loadMainground(std::string address = "", int width = -1, int height = -1);
//
//		void update();
//
//		void draw(bool drawSensor = false);
//
//		void drawCollision();
//
//	public:
//		// Get and Set Functions
//		void setMaingoundHeight(int height);
//		void setMaingroundWidth(int width);
//
//		int getMaingroundHeight();
//		int getMaingroundWidth();
//
//		void setMapSize(unsigned int x, unsigned int y);
//
//	};
//
//}