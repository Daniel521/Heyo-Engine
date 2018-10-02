#include "h_Map.h"
#include "h_heyo.h"
#include <fstream>

namespace Heyo_Platform
{

	Map::Map()
	{
		main_character = NULL;
		sensor_width = 0;
		sensor_rect = { 0,0,0,0 };

		background = NULL;
		mainground = NULL;

		rect_background.x = 0;
		rect_background.y = 0;
		rect_background.w = Heyo::Engine->graphics->getScreenWidth();
		rect_background.h = Heyo::Engine->graphics->getScreenHeight();

		rect_mainground.x = 0;
		rect_mainground.y = 0;
		rect_mainground.w = Heyo::Engine->graphics->getScreenWidth();
		rect_mainground.h = Heyo::Engine->graphics->getScreenHeight();
	}

	Map::~Map()
	{
		if (background != NULL)
		{
			delete background;
		}
		if (mainground != NULL)
		{
			delete mainground;
		}
	}

	// QUE? I cant remember what i was trying to accomplish with sensor
	bool Map::loadMainCharacter(Character & main_character, int sensor_width)
	{
		this->main_character = &main_character;

		if (sensor_width < 0)
			return false;

		this->sensor_width = sensor_width;

		sensor_rect.x = (Heyo::Engine->graphics->getScreenWidth() / 2) - (sensor_width / 2);
		sensor_rect.y = 0;
		sensor_rect.w = this->sensor_width;
		sensor_rect.h = this->main_character->getGroundLevel();
		this->main_character->sensor_rect = sensor_rect;

		return true;

	}

	bool Map::loadBackground(std::string address)
	{
		if (background != NULL)
		{
			delete background;
			background = NULL;
		}
		background = new Heyo::Sprite(Heyo::Engine->graphics);
		return background->loadSprite(address);
	}

	bool Map::loadCollision(std::string address)
	{
		Heyo::Rect rect;
		std::ifstream read;
		read.open(address);
		if (read.eof() == true)
		{
			return false;
		}

		char end_line;
		while (read.eof() == false && read.peek() != EOF)
		{
			read >> rect.x >> rect.y >> rect.w >> rect.h;
			read.get(end_line);
			coll_rect.push_back(rect);
		}

		read.close();
		return true;
	}

	bool Map::loadMainground(std::string address, int width, int height)
	{
		if (mainground != NULL)
		{
			delete mainground;
			mainground = NULL;
		}
		mainground = new Heyo::Sprite(Heyo::Engine->graphics);
		rect_mainground.w = width;
		rect_mainground.h = height;
		rect_mainground.y = height - Heyo::Engine->graphics->getScreenHeight();
		return mainground->loadSprite(address);
	}

	void Map::update()
	{
		// Heyoo
		//if (this->main_character->spr_rect.x <= )

	}

	void Map::draw(bool drawSensor)
	{
		Heyo::Engine->graphics->update(*background, rect_background);
		Heyo::Engine->graphics->update(*mainground, rect_mainground);

		if (drawSensor == true)
			Heyo::Engine->graphics->drawRect(sensor_rect, true, 100, 100, 200);
	}

	void Map::setMaingoundHeight(int height)
	{
		rect_mainground.h = height;
	}

	void Map::setMaingroundWidth(int width)
	{
		rect_mainground.w = width;
	}

	int Map::getMaingroundHeight()
	{
		return rect_mainground.h;
	}

	int Map::getMaingroundWidth()
	{
		return rect_mainground.w;
	}

}