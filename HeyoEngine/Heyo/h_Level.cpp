#include "h_Level.h"
#include "h_heyo.h"
#include <fstream>
#include <iostream>

namespace Heyo_Platform
{

	Level::Level()
	{
		main_character = NULL;
		sensor_setting = disabled;
		sensor_width = 0;
		point_main_character = { 0,0 };
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

		rect_mc = { 0,0,0,0 };
	}

	Level::~Level()
	{
		if (background != NULL)	{
			delete background;
		}
		if (mainground != NULL)	{
			delete mainground;
		}
	}

	bool Level::loadMainCharacter(Character & main_character, unsigned int sensor_width)
	{
		this->main_character = &main_character;
		point_main_character.x = Heyo::Engine->graphics->getScreenWidth() / 2 - (this->main_character->getWidth() / 2);
		point_main_character.y = this->main_character->y - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());

		this->sensor_width = sensor_width;

		if (this->sensor_width > main_character.getWidth()) {
			sensor_setting = enabled;
			sensor_rect.x = (Heyo::Engine->graphics->getScreenWidth() / 2) - (sensor_width / 2);
			sensor_rect.y = 0;
			sensor_rect.w = this->sensor_width;
			sensor_rect.h = Heyo::Engine->graphics->getScreenHeight();
		}

		return true;
	}

	bool Level::loadBackground(std::string address)
	{
		if (background != NULL) {
			delete background;
			background = NULL;
		}
		background = new Heyo::Sprite(Heyo::Engine->graphics);
		return background->loadSprite(address);
	}

	bool Level::loadCollision(std::string address)
	{
		Heyo::Rect rect;
		std::ifstream read;
		read.open(address);
		if (read.eof() == true)	{
			return false;
		}

		char end_line;
		while (read.eof() == false && read.peek() != EOF) {
			read >> rect.x >> rect.y >> rect.w >> rect.h;
			read.get(end_line);
			coll_rect.push_back(rect);
		}

		read.close();
		return true;
	}

	bool Level::loadMainground(std::string address, int width, int height)
	{
		if (mainground != NULL)
		{
			delete mainground;
			mainground = NULL;
		}
		mainground = new Heyo::Sprite(Heyo::Engine->graphics);


		bool success = mainground->loadSprite(address);
		if (success == false)
			return false;
		if (width == -1) {
			rect_mainground.w = mainground->getWidth();
		}
		else
			rect_mainground.w = width;
		if (height == -1) {
			rect_mainground.h = mainground->getHeight();
		}
		else
			rect_mainground.h = height;
		//rect_mainground.y = 0;
		rect_mainground.y = Heyo::Engine->graphics->getScreenHeight() - height;	// Shouldn't this be ScreenHeight - height? 10/7/2018
		return true;
	}

	void Level::update()
	{
		main_character->checkMapCollision(*this);

		if (main_character != NULL) {
			if (sensor_setting == enabled)
				updateMCwithSensor();
			else
				updateMCwithoutSensor();
		}
		if (mainground != NULL) {
			rect_mainground.x = Heyo::Engine->graphics->getScreenWidth()/2 - main_character->getWidth()/2 - main_character->getX();
		}
	}

	void Level::draw(bool drawSensor, bool drawCollision) {
		if (background != NULL)
			Heyo::Engine->graphics->update(*background, rect_background);
		if (mainground != NULL)
			Heyo::Engine->graphics->update(*mainground, rect_mainground);

		if (drawSensor == true && sensor_setting == enabled)
			Heyo::Engine->graphics->drawRect(sensor_rect, true, 100, 100, 200);

		if (main_character != NULL) {
			updaterect_mc();
			if (drawCollision == true) {
				Heyo::Rect temp = { rect_mc.x + main_character->collision_rect.x, rect_mc.y + main_character->collision_rect.y, main_character->collision_rect.w, main_character->collision_rect.h };
				Heyo::Engine->graphics->drawRect(temp, true, 255, 255, 0);
			}
			//Heyo::Engine->graphics->drawRect(rect_mc, false, 0, 255, 200);
			Heyo::Engine->graphics->update(*main_character->sprite, rect_mc);
		}
	}

	void Level::drawCollision()
	{
		Heyo::Rect t;
		for (std::vector<Heyo::Rect>::iterator it = coll_rect.begin(); it != coll_rect.end(); ++it) {
			t = { point_main_character.x + it->x - static_cast<int>(main_character->getX()), it->y, it->w, it->h };
			Heyo::Engine->graphics->drawRect(t, true, 0, 255, 0);
		}
	}

	void Level::drawCharacter(Character & character)
	{
		Heyo::Rect rect = { rect_mainground.x + character.getX(), character.getGroundLevel() - character.getY() - character.getHeight(), character.getWidth(), character.getHeight() };
		Heyo::Engine->graphics->update(*character.sprite, rect);
	}

	void Level::setMaingoundHeight(int height)
	{
		rect_mainground.h = height;
	}

	void Level::setMaingroundWidth(int width)
	{
		rect_mainground.w = width;
	}

	int Level::getMaingroundHeight()
	{
		return rect_mainground.h;
	}

	int Level::getMaingroundWidth()
	{
		return rect_mainground.w;
	}

	void Level::setMapSize(unsigned int x, unsigned int y)
	{
		// NOTHING, for now
	}

	void Level::updaterect_mc() {
		rect_mc.x = point_main_character.x;
		rect_mc.y = point_main_character.y;
		rect_mc.w = main_character->getWidth();
		rect_mc.h = main_character->getHeight();
	}

	void Level::updateMCwithSensor() {
		// This does not work for negative values in main_character->getX()
		// If the x coord of the character is negative, then the code slightly flips and has the collision move instead of the player at slower speeds, at faster speeds, the player moves & the collision
		// May need to an a condition statement to check if the user has a negative value for his x coordinate
		// OR ---- May make it so the player cannot go into negative values, may do that for now.
		// 10/8/18

		// the previous x & y value of main_character, e.g: main_character->getX()
		static Heyo::Point point_prev_main_xy = { static_cast<int>(this->main_character->getX()), static_cast<int>(this->main_character->getY()) };

		if (point_prev_main_xy.x < static_cast<int>(main_character->getX())) {	// Going Right
			if (point_main_character.x + main_character->getX() - point_prev_main_xy.x + main_character->getWidth() >= sensor_rect.x + sensor_rect.w) {
				point_main_character.x = sensor_rect.x + sensor_width - main_character->getWidth();
				//std::cout << "RStuck" << std::endl;
			}
			else {
				point_main_character.x = point_main_character.x + main_character->getX() - point_prev_main_xy.x;
				//std::cout << "RNot" << std::endl;
			}
		}
		else if (point_prev_main_xy.x >static_cast<int>(main_character->getX())) {	// Going left
			if (point_main_character.x - (point_prev_main_xy.x - main_character->getX()) <= sensor_rect.x) {
				point_main_character.x = sensor_rect.x;
				//std::cout << "LStuck" << std::endl;
			}
			else {
				point_main_character.x = point_main_character.x - point_prev_main_xy.x + main_character->getX();
				//std::cout << "LNot" << std::endl;
			}
		}

		point_main_character.y = this->main_character->y - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());

		point_prev_main_xy.x = main_character->getX();
		point_prev_main_xy.y = this->main_character->y - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());

	}

	void Level::updateMCwithoutSensor() {
		point_main_character.y = this->main_character->ground - this->main_character->getHeight() - static_cast<int>(this->main_character->getY());
	}

}