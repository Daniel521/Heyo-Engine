#include "h_Character.h"
#include "h_heyo.h"
#include "h_Level.h"
#include <iostream>

using namespace std;

#define gravity 70

namespace Heyo_Platform
{

	Character::Character()
	{
		sprite = new Heyo::Sprite(Heyo::Engine->graphics);
		for (int i = 0; i < 4; i++)
		{
			spr_anim[i].min = -1;
			anim_period[i] = .2f;
		}
		curr_frame = 0;
		x = 10.0f;
		y = 0.0f;
		x_speed = 400.0f;
		y_speed = 0.0f;
		spr_rect.x = static_cast<int>(x);
		spr_rect.y = static_cast<int>(400);
		spr_rect.h = 100;
		spr_rect.w = 100;
		ground = Heyo::Engine->graphics->getScreenHeight();
		jump_speed = 22;
		jumping = false;
		walking = 0;
		collision = 0;
		hitting = 0;

		collision_rect = { 0,0,spr_rect.w,spr_rect.h };
	}

	Character::~Character()
	{
		if (sprite != NULL)
		{
			delete sprite;
		}
	}

	bool Character::loadSprite(std::string address, int indiWidth, int indiHeight)
	{
		if (sprite != NULL)
		{
			delete sprite;
			sprite = NULL;
		}
		sprite = new Heyo::Sprite(Heyo::Engine->graphics);
		return sprite->loadSprite(address, indiWidth, indiHeight);
	}

	void Character::moveLeft()
	{
		if (sprite->isFlippedHor() == false)
		{
			sprite->flipHor();
		}
		if (collision != onLeft)
			x -= x_speed * Heyo::Engine->timer->seconds;
		walking = 1;
	}

	void Character::moveRight()
	{
		if (sprite->isFlippedHor() == true)
		{
			sprite->flipHor();
		}
		if (collision != onRight)
			x += x_speed * Heyo::Engine->timer->seconds;
		walking = 2;
	}

	void Character::jump()
	{
		if (jumping == false) {
			jumping = true;
			y_speed = jump_speed;
			if (spr_anim[2].min >= 0)
			{
				curr_frame = spr_anim[2].min;
			}
		}
	}

	void Character::draw(bool show_box)
	{
		if (show_box == true)
			Heyo::Engine->graphics->drawRect(spr_rect, true, 255, 200, 50);
		// Remove this after fixing default image
		if (sprite != NULL)
			Heyo::Engine->graphics->update(*sprite, spr_rect);
	}

	void Character::update()
	{
		if ((jumping == true || y != 0) && (checkCollision(onBottom) == false || y_speed > 0)) {
			jumping = true;
			jumpAnim();
			jumpUpdate();
		}
		else
		{
			if (walking == 1 && checkCollision(onLeft) == false)
				// walk left
				walkAnim();
			else if (walking == 2 && checkCollision(onRight) == false)
				// walk right
				walkAnim();
			else
				// idle
				idleAnim();
		}

		collision = none;
		walking = 0;
		hitting = 0;
		spr_rect.x = static_cast<int>(x);
		spr_rect.y = static_cast<int>(ground - spr_rect.h - y);
	}

	bool Character::checkMapCollision(Level& map)
		// Fix this function!!
		// Change spr_rect and how collisions check
		// I would say to get rid of ground (make the bottom side of the screen be the ground basically)
		// And make HeyoCollision make the rectangles measure from down to up, so the bottom side of the screen is y = 0, and the top is y = ScreenHeight
	{

		Heyo::Rect character_rect;
		if (collision_rect.h == 0)
			character_rect = { spr_rect.x, spr_rect.y, spr_rect.x, spr_rect.y };
		else
			character_rect = { spr_rect.x + collision_rect.x, spr_rect.y + collision_rect.y, collision_rect.w, collision_rect.h };

		Heyo::Rect collide;
		//char_rect = { static_cast<int>(getX()), Heyo::Engine->graphics->getScreenHeight() -  getY(), getWidth(), getHeight() };
		for (std::vector<Heyo::Rect>::iterator i = map.coll_rect.begin(); i != map.coll_rect.end(); i++)
		{
			if (SDL_IntersectRect(&*i, &character_rect, &collide) == true)
			{
				if (collide.w > collide.h/2)
				{
					if (collide.y == i->y) {
						collision |= onBottom;
						jumping = false;
						y_speed = 0;
						setY(ground - collide.y - 1 - (getWidth() - collision_rect.y - collision_rect.h)); // Can we simplify this math?
						continue;
						//return true;
					}
					else {
						collision |= onTop;
						y_speed = 0;
						setY(ground - collide.y - collide.h - getHeight() + collision_rect.y); // Check math as well, please
						continue;
						//return true;
					}
				}
				else if (collide.x == i->x)
				{
					collision |= onRight;
					//setX(collide.x - character_rect.w + 1);
					setX(collide.x - collision_rect.x - collision_rect.w + 1);
					continue;
					//return true;
				}
				else
				{
					collision |= onLeft;
					setX(collide.x + collide.w - collision_rect.x - 1);
					continue;
					//return true;
				}
			}
		}

		//for (std::vector<Heyo::Rect>::iterator i = map.coll_rect.begin(); i != map.coll_rect.end(); i++)
		//{
		//	if (SDL_IntersectRect(&*i, &spr_rect, &collide) == true)
		//	{
		//		if (collide.w > collide.h / 2)
		//		{
		//			if (collide.y == i->y) {
		//				collision = onBottom;
		//				jumping = false;
		//				y_speed = 0;
		//				setY(ground - collide.y - 1);
		//				return true;
		//			}
		//			else {
		//				collision = onTop;
		//				y_speed = 0;
		//				setY(ground - collide.y - collide.h - getHeight());
		//				return true;
		//			}
		//		}
		//		else if (collide.x == i->x)
		//		{
		//			collision = onRight;
		//			setX(collide.x - getWidth() + 1);
		//			return true;
		//		}
		//		else
		//		{
		//			collision = onLeft;
		//			setX(collide.x + collide.w - 1);
		//			return true;
		//		}
		//	}
		//}



		//collision = none;
		return true;
	}

	void Character::setCollisonRect(Heyo::Rect coll)
	{
		collision_rect = coll;
	}

	bool Character::checkCollision(CollisionLabel col)
	{
		return (collision&col) == col;
	}

	void Character::setIdleAnim(int first, int last)
	{
		spr_anim[0] = { first,last };
	}

	void Character::setJumpAnim(int first, int last)
	{
		spr_anim[2].min = first;
		spr_anim[2].max = last;
	}

	void Character::setWalkAnim(int first, int last)
	{
		spr_anim[1].min = first;
		spr_anim[1].max = last;
	}

	void Character::setHeight(int height) {
		collision_rect.y = static_cast<int>(collision_rect.y * ((1.0f * height) / spr_rect.h));
		collision_rect.h =  static_cast<int>(collision_rect.h * ((1.0f * height) / spr_rect.h));

		spr_rect.h = height;
	}

	void Character::setWidth(int width) {
		collision_rect.x = static_cast<int>(collision_rect.x * ((1.0f* width) / spr_rect.w));
		collision_rect.w =  static_cast<int>(collision_rect.w * ((1.0f* width) / spr_rect.w));

		spr_rect.w = width;
	}

	void Character::setX(float x)
	{
		this->x = x;
	}

	void Character::setY(float y)
	{
		this->y = y;
	}

	void Character::setX_Speed(float x_speed)
	{
		this->x_speed = x_speed;
	}

	void Character::setY_Speeed(float y_speed)
	{
		this->y_speed = y_speed;
	}

	void Character::setJumpSpeed(float jump_speed)
	{
		this->jump_speed = jump_speed;
	}

	bool Character::isJumping()
	{
		return jumping;
	}

	float Character::getJumpSpeed()
	{
		return jump_speed;
	}

	int Character::getGroundLevel()
	{
		return ground;
	}

	float Character::getX()
	{
		return x;
	}

	float Character::getY()
	{
		return y;
	}

	int Character::getHeight()
	{
		return spr_rect.h;
	}

	int Character::getWidth()
	{
		return spr_rect.w;
	}

	float Character::getX_Speed()
	{
		return x_speed;
	}

	float Character::getY_Speed()
	{
		return y_speed;
	}

	void Character::setIdleFramePeriod(float seconds)
	{
		anim_period[0] = seconds;
	}

	void Character::setJumpFramePeriod(float seconds)
	{
		anim_period[2] = seconds;
	}

	void Character::setWalkFramePeriod(float seconds)
	{
		anim_period[1] = seconds;
	}

	/* Helper Functions */

	void Character::jumpUpdate()
	{
		y_speed -= gravity * Heyo::Engine->timer->seconds;
		y += y_speed;
		if (y <= 0)
		{
			y = 0;
			y_speed = 0;
			jumping = false;
		}
	}

	void Character::idleAnim()
	{
		if (spr_anim[0].min < 0)
			return;
		static float time_since_last_anim = 0;
		time_since_last_anim += Heyo::Engine->timer->seconds;
		if (curr_frame < spr_anim[0].min || curr_frame >= spr_anim[0].max)
		{
			curr_frame = spr_anim[0].min;
		}
		if (time_since_last_anim >= anim_period[0])
		{
			time_since_last_anim = 0;
			curr_frame++;
		}
		sprite->swap(curr_frame);
	}

	void Character::jumpAnim()
	{
		if (spr_anim[2].min < 0)
			return;
		static float time_since_last_anim = 0;
		time_since_last_anim += Heyo::Engine->timer->seconds;
		if (curr_frame >= spr_anim[2].max)
		{
			return;
		}
		if (time_since_last_anim >= anim_period[2])
		{
			time_since_last_anim = 0;
			curr_frame++;
		}
		sprite->swap(curr_frame);
	}

	void Character::walkAnim()
	{
		if (spr_anim[1].min < 0)
			return;
		static float time_since_last_anim = 0;
		time_since_last_anim += Heyo::Engine->timer->seconds;
		if (curr_frame < spr_anim[1].min || curr_frame >= spr_anim[1].max)
		{
			curr_frame = spr_anim[1].min;
		}
		if (time_since_last_anim >= anim_period[1])
		{
			time_since_last_anim = 0;
			curr_frame++;
		}
		sprite->swap(curr_frame);

	}

	void Character::setGroundLevel(int y)
	{
		ground = y;
	}

}