#pragma once

#include "h_Sprite.h"


// Base class used to make all my characters, for now atleast.

namespace Heyo_Platform
{
	// Classes used to make characters for a platform game, idk how to spell

	class Character
	{
	public:

		Heyo::Sprite * sprite;
		// 0. idle, 1. walk, 2. jump, 3. die
		Heyo::Range spr_anim[4];
		// 0. idle, 1. walk, 2. jump, 3. die
		float anim_period[4];
		short curr_frame;

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

		void draw(bool show_box = false);
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
		void setWalkAnim(int first, int last);

		// set the amount of seconds a frame is shown
		void setIdleFramePeriod(float seconds);
		void setJumpFramePeriod(float seconds);
		void setWalkFramePeriod(float seconds);

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

		void walkAnim();

	};

}
