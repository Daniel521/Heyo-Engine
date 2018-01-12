#include "h_Character.h"
#include "h_heyo.h"
#include <iostream>
using namespace std;


	Character::Character()
		//sprite(NULL),
		//sprite_rect({ 0,0,0,0 }),
		//curr_frame(0),
		//x(0),
		//y(0),
		//x_speed(100.0f),
		//y_speed(100.0f),
		//is_jumping(false),
		//width(20),
		//height(20),
		//spr_range_idle({ -1,-1 }),
		//spr_range_moveLeft({ -1,-1 }),
		//spr_range_moveRight({ -1,-1 }),
		//spr_range_jump({-1,-1})
	{
		sprite = NULL;
		sprite_rect = { 0,0,0,0 };
		curr_frame = 0;
		x = 0;
		y = 0;
		x_speed = 100.0f;
		y_speed = 100.0f;
		jumping = false;
		width = 20;
		height = 20;
		spr_range_idle = { -1,0 };
		spr_range_move = { -1,0 };
		spr_range_jump = { -1,0 };

	}

	Character::~Character()
	{
		if (sprite != NULL)
		{
			delete sprite;
		}
	}

	bool Character::loadSprite(std::string addresss, int indiWidth, int indiHeight)
	{
		if (sprite != NULL)
		{
			delete sprite;
			sprite = NULL;
		}
		sprite = new Heyo::Sprite(Heyo::Engine->graphics);
		sprite_rect = {static_cast<int>(x),static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height),width,height };

		return sprite->loadSprite(addresss, indiWidth, indiHeight);

		// we'll use this for main characters like greg, but for now, no
		//sprite_rect = { *Heyo::Engine->graphics->SCREEN_WIDTH - width/2,*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height,width,height };
		// only difference is the x
	}

	void Character::update()
	{
		static float time_since_last_anim = 0;
		time_since_last_anim += Heyo::Engine->timer->seconds;

		// Jumping is happening
		if (y_speed != 0)
		{
			jumpUpdate();
		//	jumpAnim(time_since_last_anim);
		}
		//// Walking is happening
		//else if (x_speed != 0)
		//{
		//	walkAnim(time_since_last_anim);
		//}
		//// Idle is happening
		//else
		//{
		//	idleAnim(time_since_last_anim);
		//	curr_frame_walk = sp_greg_walk.min;
		//}

		//sprite_rect = { *Heyo::Engine->graphics->SCREEN_WIDTH - width / 2,*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height,width,height };
		//sprite_rect = { static_cast<int>(x),static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height),width,height };
		sprite_rect.x = static_cast<int>(x);
		sprite_rect.y = static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height - y);
		sprite_rect.w = width;
		sprite_rect.h = height;
	}

	void Character::moveLeft()
	{
		if (sprite->isFlippedHor() == false)
		{
			sprite->flipHor();
		}
		x -= x_speed * Heyo::Engine->timer->seconds;
		//sprite_rect.x = static_cast<int>(x);
	}

	void Character::moveRight()
	{
		if (sprite->isFlippedHor() == true)
		{
			sprite->flipHor();
		}
		x += x_speed * Heyo::Engine->timer->seconds;
		sprite_rect.x = static_cast<int>(x);
	}

	void Character::jump()
	{
		y_curr_speed = y_speed;
		jumping = true;
		// $$FALL SOUND
	}

	void Character::setX(float x)
	{
		this->x = x;
	}

	void Character::setY(float y)
	{
		this->y = y;
	}

	float Character::getX()
	{
		return x;
	}

	float Character::getY()
	{
		return y;
	}

	void Character::setX_Speed(float x_speed)
	{
		this->x_speed = x_speed;
	}

	void Character::setY_Speed(float y_speed)
	{
		this->y_speed = y_speed;
	}

	float Character::getX_Speed()
	{
		return x_speed;
	}

	float Character::getY_Speed()
	{
		return y_speed;
	}

	void Character::setIdleRange(Heyo::Range range)
	{
		this->spr_range_idle = range;
	}

	void Character::setMoveRange(Heyo::Range range)
	{
		this->spr_range_move = range;
	}

	void Character::setJumpRange(Heyo::Range range)
	{
		this->spr_range_jump = range;
	}

	bool Character::isJumping()
	{
		return jumping;
	}

	void Character::jumpUpdate()
	{
		y_curr_speed -= 1400 * Heyo::Engine->timer->seconds;

		y += y_curr_speed * Heyo::Engine->timer->seconds;
		if (y <= 0)
		{
			y = 0;
			y_curr_speed = 0;
			jumping = false;
		}
	}