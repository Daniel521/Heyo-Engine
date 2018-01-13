#pragma once

#include "h_Sprite.h"


// Base class used to make all my characters, for now atleast.


// Classes used to make characters for a platform game, idk how to spell

//class Character
//{
//public:
//	Heyo::Sprite * sprite;
//
//	// sprite_rect w/ respect to the screen, NOT THE MAP!
//	Heyo::Rect sprite_rect;
//
//	int curr_frame;
//	float y_curr_speed;
//	float x;
//	float y;
//	float x_speed;
//	float y_speed;
//	bool jumping;
//	int width;
//	int height;
//	Heyo::Range spr_range_idle;
//	Heyo::Range spr_range_move;
//	Heyo::Range spr_range_jump;
//
//public:
//	Character();
//	~Character();
//
//	// - Loads a sprite from the specified addresss, ex: Data/Sprite/greg.png
//	// - Only loads png for now
//	// - indiWidth and indiHeight specifies the width and height of each
//	//	individual sprite in the whole spritesheet, leave as -1 to cover the
//	//	whole width or height.
//	bool loadSprite(std::string addresss, int indiWidth = -1, int indiHeight = -1);
//
//	// Specifies the current frame of the sprite
//	//Uint32 getCurrentFrame();
//
//	void update();
//
//	void moveLeft();
//
//	void moveRight();
//
//	void jump();
//
//	void setX(float x);
//
//	void setY(float y);
//
//	float getX();
//
//	float getY();
//
//	void setX_Speed(float x_speed);
//
//	void setY_Speed(float y_speed);
//
//	float getX_Speed();
//
//	float getY_Speed();
//
//	void setIdleRange(Heyo::Range range);
//
//	void setMoveRange(Heyo::Range range);
//
//	void setJumpRange(Heyo::Range range);
//
//	bool isJumping();
//
//private:
//
//	void jumpUpdate();
//
//	//void idleAnim();
//	
//	//void moveLeftAnim();
//
//	//void moveRightAnim();
//
//	//void jumpAnim();
//
//};

class Character
{
public:

	Heyo::Sprite * sprite;
	// 0. idle, 1. walk, 2. jump, 3. die
	Heyo::Range spr_anim[4];
	// 0. idle, 1. walk, 2. jump, 3. die
	float anim_period[4];
	int curr_frame;

	Heyo::Rect spr_rect;

	float x;
	float y;
	float x_speed;
	float jump_speed;
	float y_speed;
	// 0. idle, 1. left, 2. right
	unsigned char walking;
	bool jumping;
	
	int ground;

public:

	Character();
	~Character();

	bool loadSprite(std::string address, int indiWidth = -1, int indiHeight = -1);


	void moveLeft();
	void moveRight();
	void jump();

	void draw();
	void update();

public:
	// Mutators and Accessors

	// Specifies the speed from what the character
	// jumps from.
	void setJumpSpeed(float jump_speed);

	// this function specifies how many frames from top to ground
	// is the ground located at.
	void setGroundLevel(int y);

	// specifies the frames that are associated to idle anim
	// frame 0 is the first frame, like with arrays.
	void setIdleAnim(int first, int last);
	void setJumpAnim(int first, int last);

	// set the amount of seconds a frame is shown
	void setIdleFramePeriod(float seconds);
	void setJumpFramePeriod(float seconds);

	void setHeight(int height);
	void setWidth(int width);

	void setX(float x);
	void setY(float y);

	void setX_Speed(float x_speed);
	void setY_Speeed(float y_speed);


	bool isJumping();

	float getJumpSpeed();
	int getGroundLevel();

	float getX();
	float getY();

	int getHeight();
	int getWidth();

	float getX_Speed();
	float getY_Speed();




private:
	// Function helpers these functions are used to help my other functions
	void jumpUpdate();

	void idleAnim();

	void jumpAnim();

};