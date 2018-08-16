#include "h_Map.h"
#include "h_heyo.h"
#include <fstream>
#include <iostream>

namespace Heyo_Platform
{
	Map::Map()
	{
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

		string coll_type;
		string name;
		char end_line;
		while (read.eof() == false && read.peek() != EOF)
		{
			read >> coll_type;
			if (coll_type == "coll:")
			{
			read >> rect.x >> rect.y >> rect.w >> rect.h;
			read.get(end_line);
			coll_list.push_back(rect);
			}
			else if (coll_type == "spawn:")
			{
				Spawn t_spawn;
				read >> t_spawn.name;
				read >> t_spawn.point.x >> t_spawn.point.y;
				read.get(end_line);
				spawn_list.push_back(t_spawn);
			}
			else if (coll_type == "enc:")
			{
				read >> name;
				read >> rect.x >> rect.y >> rect.w >> rect.h;
				read.get(end_line);
				enc_list.push_back({rect,name});
			}
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
	}

	void Map::draw()
	{
		if (background != NULL)
			Heyo::Engine->graphics->update(*background, rect_background);
		if (mainground != NULL)
			Heyo::Engine->graphics->update(*mainground, rect_mainground);
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