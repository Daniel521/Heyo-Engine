#include "h_Character.h"
#include "h_heyo.h"
#include <iostream>
using namespace std;

#define gravity 80

	//Character::Character()
	//	//sprite(NULL),
	//	//sprite_rect({ 0,0,0,0 }),
	//	//curr_frame(0),
	//	//x(0),
	//	//y(0),
	//	//x_speed(100.0f),
	//	//y_speed(100.0f),
	//	//is_jumping(false),
	//	//width(20),
	//	//height(20),
	//	//spr_range_idle({ -1,-1 }),
	//	//spr_range_moveLeft({ -1,-1 }),
	//	//spr_range_moveRight({ -1,-1 }),
	//	//spr_range_jump({-1,-1})
	//{
	//	sprite = NULL;
	//	sprite_rect = { 0,0,0,0 };
	//	curr_frame = 0;
	//	x = 0;
	//	y = 0;
	//	x_speed = 100.0f;
	//	y_speed = 100.0f;
	//	jumping = false;
	//	width = 20;
	//	height = 20;
	//	spr_range_idle = { -1,0 };
	//	spr_range_move = { -1,0 };
	//	spr_range_jump = { -1,0 };

	//}

	//Character::~Character()
	//{
	//	if (sprite != NULL)
	//	{
	//		delete sprite;
	//	}
	//}

	//bool Character::loadSprite(std::string addresss, int indiWidth, int indiHeight)
	//{
	//	if (sprite != NULL)
	//	{
	//		delete sprite;
	//		sprite = NULL;
	//	}
	//	sprite = new Heyo::Sprite(Heyo::Engine->graphics);
	//	sprite_rect = {static_cast<int>(x),static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height),width,height };

	//	return sprite->loadSprite(addresss, indiWidth, indiHeight);

	//	// we'll use this for main characters like greg, but for now, no
	//	//sprite_rect = { *Heyo::Engine->graphics->SCREEN_WIDTH - width/2,*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height,width,height };
	//	// only difference is the x
	//}

	//void Character::update()
	//{
	//	static float time_since_last_anim = 0;
	//	time_since_last_anim += Heyo::Engine->timer->seconds;

	//	// Jumping is happening
	//	if (y_speed != 0)
	//	{
	//		jumpUpdate();
	//	//	jumpAnim(time_since_last_anim);
	//	}
	//	//// Walking is happening
	//	//else if (x_speed != 0)
	//	//{
	//	//	walkAnim(time_since_last_anim);
	//	//}
	//	//// Idle is happening
	//	//else
	//	//{
	//	//	idleAnim(time_since_last_anim);
	//	//	curr_frame_walk = sp_greg_walk.min;
	//	//}

	//	//sprite_rect = { *Heyo::Engine->graphics->SCREEN_WIDTH - width / 2,*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height,width,height };
	//	//sprite_rect = { static_cast<int>(x),static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height),width,height };
	//	sprite_rect.x = static_cast<int>(x);
	//	sprite_rect.y = static_cast<int>(*Heyo::Engine->graphics->SCREEN_HEIGHT - (*Heyo::Engine->graphics->SCREEN_HEIGHT * .08f) - height - y);
	//	sprite_rect.w = width;
	//	sprite_rect.h = height;
	//}

	//void Character::moveLeft()
	//{
	//	if (sprite->isFlippedHor() == false)
	//	{
	//		sprite->flipHor();
	//	}
	//	x -= x_speed * Heyo::Engine->timer->seconds;
	//	//sprite_rect.x = static_cast<int>(x);
	//}

	//void Character::moveRight()
	//{
	//	if (sprite->isFlippedHor() == true)
	//	{
	//		sprite->flipHor();
	//	}
	//	x += x_speed * Heyo::Engine->timer->seconds;
	//	sprite_rect.x = static_cast<int>(x);
	//}

	//void Character::jump()
	//{
	//	y_curr_speed = y_speed;
	//	jumping = true;
	//	// $$FALL SOUND
	//}

	//void Character::setX(float x)
	//{
	//	this->x = x;
	//}

	//void Character::setY(float y)
	//{
	//	this->y = y;
	//}

	//float Character::getX()
	//{
	//	return x;
	//}

	//float Character::getY()
	//{
	//	return y;
	//}

	//void Character::setX_Speed(float x_speed)
	//{
	//	this->x_speed = x_speed;
	//}

	//void Character::setY_Speed(float y_speed)
	//{
	//	this->y_speed = y_speed;
	//}

	//float Character::getX_Speed()
	//{
	//	return x_speed;
	//}

	//float Character::getY_Speed()
	//{
	//	return y_speed;
	//}

	//void Character::setIdleRange(Heyo::Range range)
	//{
	//	this->spr_range_idle = range;
	//}

	//void Character::setMoveRange(Heyo::Range range)
	//{
	//	this->spr_range_move = range;
	//}

	//void Character::setJumpRange(Heyo::Range range)
	//{
	//	this->spr_range_jump = range;
	//}

	//bool Character::isJumping()
	//{
	//	return jumping;
	//}

	//void Character::jumpUpdate()
	//{
	//	y_curr_speed -= 1400 * Heyo::Engine->timer->seconds;

	//	y += y_curr_speed * Heyo::Engine->timer->seconds;
	//	if (y <= 0)
	//	{
	//		y = 0;
	//		y_curr_speed = 0;
	//		jumping = false;
	//	}
	//}

Character::Character()
{
	sprite = NULL;
	for (int i = 0; i < 4; i++)
	{
		spr_anim[i].min = -1;
		anim_period[i] = .2f;
	}
	curr_frame = 0;
	x = 10.0f;
	y = 0.0f;
	x_speed = 500.0f;
	y_speed = 0.0f;
	spr_rect.x = static_cast<int>(x);
	spr_rect.y = static_cast<int>(400);
	spr_rect.h = 100;
	spr_rect.w = 100;
	ground = 300;
	jump_speed = 22;
	jumping = false;
	walking = 0;
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
	x -= x_speed * Heyo::Engine->timer->seconds;
	walking = 1;
}

void Character::moveRight()
{
	x += x_speed * Heyo::Engine->timer->seconds;
	walking = 2;
}

void Character::jump()
{
	jumping = true;
	y_speed = jump_speed;
	if (spr_anim[2].min >= 0)
	{
		curr_frame = spr_anim[2].min;
	}
}

void Character::draw()
{
	Heyo::Engine->graphics->update(*sprite, spr_rect);
}

void Character::update()
{
	if (jumping == true || y != 0)
	{
		jumpAnim();
		jumpUpdate();
	}
	else
	{
		if (walking == 1)
		{
			// walk left
		}
		else if (walking == 2)
		{
			// walk right
		}
		else
		{
			// idle
			idleAnim();
		}
	}

	walking = 0;
	spr_rect.x = static_cast<int>(x);
	spr_rect.y = static_cast<int>(ground - spr_rect.h - y);
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

void Character::setHeight(int height)
{
	spr_rect.h = height;
}

void Character::setWidth(int width)
{
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

void Character::setGroundLevel(int y)
{
	ground = y;
}
