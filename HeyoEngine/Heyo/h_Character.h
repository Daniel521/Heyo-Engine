#pragma once

#include "h_Sprite.h"


// Base class used to make all my characters, for now atleast.


// Classes used to make characters for a platform game, idk how to spell
namespace HeyoPlat
{

	class Character
	{
	public:
		Heyo::Sprite * sprite;
		// sprite_rect w/ respect to the screen, NOT THE MAP!
		Heyo::Rect sprite_rect;

		int curr_frame;
		float y_curr_speed;

	public:
		float x;
		float y;
		float x_speed;
		float y_speed;
		bool is_jumping;
		int width;
		int height;
		Heyo::Range spr_range_idle;
		Heyo::Range spr_range_moveLeft;
		Heyo::Range spr_range_moveRight;
		Heyo::Range spr_range_jump;

	public:
		Character();
		~Character();

		// - Loads a sprite from the specified addresss, ex: Data/Sprite/greg.png
		// - Only loads png for now
		// - indiWidth and indiHeight specifies the width and height of each
		//	individual sprite in the whole spritesheet, leave as -1 to cover the
		//	whole width or height.
		bool loadSprite(std::string addresss, int indiWidth = -1, int indiHeight = -1);

		// Specifies the current frame of the sprite
		//Uint32 getCurrentFrame();

		void update();

		void moveLeft();

		void moveRight();

		void jump();

		void setX(int x) { this->x = x; }

	private:

		void jumpUpdate();

		//void idleAnim();
	
		//void moveLeftAnim();

		//void moveRightAnim();

		//void jumpAnim();

	};

}


