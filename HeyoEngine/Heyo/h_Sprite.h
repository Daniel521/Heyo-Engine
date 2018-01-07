#pragma once

/*
*	h_Sprite.h
*	- This is used to grab images and turn them into sprites. Animated if available.
*
*
*
*
*/

//#include "..\SDL2\include\SDL.h"
#include <SDL.h>
#include <string>
#include "h_Image.h"

// Used to determine how far a certain
// animation goes in a sprite
struct range {
	int min;
	int max;
};

namespace Heyo {

	class Graphics;

	typedef SDL_Point Point;
	typedef SDL_Point Coord;

	class Sprite
	{
	private:
		Image m_image;
		Rect * m_rect;
		int m_numFrames;	// Total number of frames
		int m_curFrame;		// Current frame count, 0 is first frame
		int m_spriteWidth;
		int m_spriteHeight;


		int m_destWidth;
		int m_destHeight;

	private:

	public:
		Sprite();
		Sprite(const Graphics * graphics);
		~Sprite();

		void init(Graphics * graphics);


		// Loads the PNG and determines the number of sprites in the sprite sheet
		// imgAddress: the address of the img
		// graphics: graphics where you will use the sprite
		// indiWidth: width of each sprite
		// indiHeight: height of each sprite
		// numX: num of sprites along x-axis
		// numY: num of sprites along y-axis
		bool loadSprite(std::string imgAddress, int indiWidth = -1, int indiHeight = -1);

		// returns sprite sheet's total width
		int getTotalWidth();
		// returns sprite sheet's total height
		int getTotalHeight();
		// returns each frame's width
		int getWidth();
		// returns each frame's height
		int getHeight();

		// returns a Rect of the current frame
		const Rect &  getcurRect();

		// changes the current frame, 0 is first frame
		Sprite & operator[](int val);

		void swap(int val);
		Sprite & operator++();
		Sprite & operator--();
		//flipping stuff
		// DOES NOT WORK YET!!!!! I believe it will flip the sprite but also mess up the numbering.
		void flipVer();
		void flipHor();

		// modify image
		void setColor(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255) { m_image.setColor(red, green, blue); }
		void setAlpha(Uint8 alpha) { m_image.setAlpha(alpha); }
		//flip check
		bool isFlippedVer()	{ return m_image.isFlippedVer(); }
		bool isFlippedHor() { return m_image.isFlippedHor(); }

		//angle stuff
		void setAngle(double angle) { m_image.setAngle(angle); }
		double getAngle()	{ return m_image.getAngle(); }

		int getcurFrame()	{ return m_curFrame; }
		int gettotalFrames();

		void setdestWidth(int width);
		void setdestHeight(int height);

		int getdestWidth()	{ return m_destWidth; }
		int getdestHeight() { return m_destHeight; }


		friend class Graphics;
	};

}