//#include "h_Map.h"
//#include "h_heyo.h"
//#include <fstream>
//#include <iostream>
//
//namespace Heyo_Platform
//{
//
//	Map::Map()
//	{
//		main_character = NULL;
//		point_main_character = { 0,0 };
//		point_prev_main_xy = { 0,0 };
//		sensor_width = 0;
//		sensor_rect = { 0,0,0,0 };
//
//		background = NULL;
//		mainground = NULL;
//
//		rect_background.x = 0;
//		rect_background.y = 0;
//		rect_background.w = Heyo::Engine->graphics->getScreenWidth();
//		rect_background.h = Heyo::Engine->graphics->getScreenHeight();
//
//		rect_mainground.x = 0;
//		rect_mainground.y = 0;
//		rect_mainground.w = Heyo::Engine->graphics->getScreenWidth();
//		rect_mainground.h = Heyo::Engine->graphics->getScreenHeight();
//
//		rect_map = { 0,0,0,0 };
//		x_offset = 0;
//	}
//
//	Map::~Map()
//	{
//		if (background != NULL)
//		{
//			delete background;
//		}
//		if (mainground != NULL)
//		{
//		delete mainground;
//		}
//	}
//
//	bool Map::loadMainCharacter(Character & main_character, unsigned int sensor_width)
//	{
//		this->main_character = &main_character;
//		point_main_character.x = Heyo::Engine->graphics->getScreenWidth()/2 - (this->main_character->getWidth() / 2);
//		point_main_character.y = Heyo::Engine->graphics->getScreenHeight() - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());
//		point_prev_main_xy = { static_cast<int>(this->main_character->getX()), static_cast<int>(this->main_character->getY()) };
//
//
//
//		this->sensor_width = sensor_width;
//
//		sensor_rect.x = (Heyo::Engine->graphics->getScreenWidth() / 2) - (sensor_width / 2);
//		sensor_rect.y = 0;
//		sensor_rect.w = this->sensor_width;
//		sensor_rect.h = Heyo::Engine->graphics->getScreenHeight();
//		this->main_character->sensor_rect = sensor_rect;
//
//		return true;
//	}
//
//	bool Map::loadBackground(std::string address)
//	{
//		if (background != NULL)
//		{
//			delete background;
//			background = NULL;
//		}
//		background = new Heyo::Sprite(Heyo::Engine->graphics);
//		return background->loadSprite(address);
//	}
//
//	bool Map::loadCollision(std::string address)
//	{
//		Heyo::Rect rect;
//		std::ifstream read;
//		read.open(address);
//		if (read.eof() == true)
//		{
//			return false;
//		}
//
//		char end_line;
//		while (read.eof() == false && read.peek() != EOF)
//		{
//			read >> rect.x >> rect.y >> rect.w >> rect.h;
//			read.get(end_line);
//			coll_rect.push_back(rect);
//		}
//
//		read.close();
//		return true;
//	}
//
//	bool Map::loadMainground(std::string address, int width, int height)
//	{
//		if (mainground != NULL)
//		{
//			delete mainground;
//			mainground = NULL;
//		}
//		mainground = new Heyo::Sprite(Heyo::Engine->graphics);
//		rect_mainground.w = width;
//		rect_mainground.h = height;
//		rect_mainground.y = height - Heyo::Engine->graphics->getScreenHeight();	// Shouldn't this be ScreenHeight - height? 10/7/2018
//		return mainground->loadSprite(address);
//	}
//
//	void Map::update()
//	{
//		// This does not work for negative values in main_character->getX()
//		// If the x coord of the character is negative, then the code slightly flips and has the collision move instead of the player at slower speeds, at faster speeds, the player moves & the collision
//		// May need to an a condition statement to check if the user has a negative value for his x coordinate
//		// OR ---- May make it so the player cannot go into negative values, may do that for now.
//		// 10/8/18
//		if (main_character != NULL) {
//			if (point_prev_main_xy.x < static_cast<int>(main_character->getX())) {	// Going Right
//				if (point_main_character.x + main_character->getX() - point_prev_main_xy.x + main_character->getWidth() >= sensor_rect.x + sensor_rect.w) {
//					point_main_character.x = sensor_rect.x + sensor_width - main_character->getWidth();
//					//std::cout << "RStuck" << std::endl;
//				}
//				else {
//					point_main_character.x = point_main_character.x + main_character->getX() - point_prev_main_xy.x;
//					//std::cout << "RNot" << std::endl;
//				}
//			}
//			else if (point_prev_main_xy.x >static_cast<int>(main_character->getX())) {	// Going left
//				if (point_main_character.x - (point_prev_main_xy.x - main_character->getX()) <= sensor_rect.x) {
//					point_main_character.x = sensor_rect.x;
//					//std::cout << "LStuck" << std::endl;
//				}
//				else {
//					point_main_character.x = point_main_character.x - point_prev_main_xy.x + main_character->getX();
//					//std::cout << "LNot" << std::endl;
//				}
//			}
//
//			point_main_character.y = Heyo::Engine->graphics->getScreenHeight() - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());
//
//			point_prev_main_xy.x = main_character->getX();
//			point_prev_main_xy.y = Heyo::Engine->graphics->getScreenHeight() - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());
//
//		}
//
//	}
//
//	void Map::draw(bool drawSensor)
//	{
//		if (background != NULL)
//			Heyo::Engine->graphics->update(*background, rect_background);
//		if (mainground != NULL)
//			Heyo::Engine->graphics->update(*mainground, rect_mainground);
//
//		if (drawSensor == true)
//			Heyo::Engine->graphics->drawRect(sensor_rect, true, 100, 100, 200);
//
//		if (main_character != NULL) {
//			//Heyo::Rect temp = { 0,0,0,0 };
//			//temp.x = point_main_character.x;
//			//temp.y = point_main_character.y;
//			//temp.w = main_character->getWidth();
//			//temp.h = main_character->getHeight();
//			Heyo::Engine->graphics->update(*main_character->sprite, Heyo::Rect({ point_main_character.x, point_main_character.y, main_character->getWidth(), main_character->getHeight() }));
//		}
//	}
//
//	void Map::drawCollision()
//	{
//		for (std::vector<Heyo::Rect>::iterator it = coll_rect.begin(); it != coll_rect.end(); ++it) {
//			Heyo::Rect t = { point_main_character.x + it->x - static_cast<int>(main_character->getX()), it->y, it->w, it->h };
//			//std::cout << "x: " << t.x << std::endl;
//			//std::cout << "y: " << t.y << std::endl;
//			Heyo::Engine->graphics->drawRect(t, true, 0, 255, 0);
//		}
//	}
//
//	void Map::setMaingoundHeight(int height)
//	{
//		rect_mainground.h = height;
//	}
//
//	void Map::setMaingroundWidth(int width)
//	{
//		rect_mainground.w = width;
//	}
//
//	int Map::getMaingroundHeight()
//	{
//		return rect_mainground.h;
//	}
//
//	int Map::getMaingroundWidth()
//	{
//		return rect_mainground.w;
//	}
//
//	void Map::setMapSize(unsigned int x, unsigned int y)
//	{
//		rect_map.x = 0;
//		rect_map.y = 0;
//		rect_map.w = x;
//		rect_map.h = y;
//	}
//
//}