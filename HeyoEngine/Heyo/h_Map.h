#pragma once
/**************************
//		Map Class
//	This  class is used to make platform maps.
**************************/
#include "h_Sprite.h"
#include <vector>


namespace Heyo_Platform
{
	class Map
	{
	private:
		class Spawn
		{
		public:
			Heyo::Point point;
			std::string name;
		};
		class Encounter
		{
		public:
			Heyo::Rect rect;
			std::string name;
		};
	public:
	// Private variables --- Public for now...	1/13/18
		Heyo::Sprite * background;
		Heyo::Rect rect_background;
		Heyo::Sprite * mainground;
		Heyo::Rect rect_mainground;

		std::vector<Heyo::Rect> coll_list;
		std::vector<Spawn> spawn_list;
		std::vector<Encounter> enc_list;
	public:
		// Main functions
		Map();
		~Map();

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

		void draw();

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