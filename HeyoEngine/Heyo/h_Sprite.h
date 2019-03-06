#pragma once

/*
*	h_Sprite.h
*	- This is used to grab images and turn them into sprites. Animated if available.
*
*/

//#include "..\SDL2\include\SDL.h"
#include <SDL.h>
#include <string>
#include "h_Image.h"

namespace Heyo {
	class Graphics;
	typedef SDL_Point Point;
	typedef SDL_Point Coord;

	struct Range {
		int min;
		int max;
	};

	class Sprite {
	public:
		Sprite() : m_rect(nullptr), m_num_frames(0), m_cur_frame(0),
			m_sprite_width(0), m_sprite_height(0) {}
		~Sprite() { if (m_rect != nullptr) delete[] m_rect; }

		// Loads the PNG and determines the number of sprites in the sprite sheet
		// imgAddress: the address of the img
		// graphics: graphics where you will use the sprite
		// indiWidth: width of each sprite
		// indiHeight: height of each sprite
		// numX: num of sprites along x-axis
		// numY: num of sprites along y-axis
		bool load(const Graphics* graphics, std::string imgAddress, int indiWidth = -1, int indiHeight = -1);

		// returns sprite sheet's total width
		int totalWidth() { return m_image.width(); }
		// returns sprite sheet's total height
		int totalHeight() { return m_image.height(); }
		// returns each frame's width
		int width() { return m_sprite_width; }
		// returns each frame's height
		int height() { return m_sprite_height; }

		// returns a Rect of the current frame
		const Rect&  curRect() { return m_rect[m_cur_frame]; }

		// changes the current frame, 0 is first frame
		Sprite& operator[](int val);
		void swap(int val);
		Sprite& operator++();
		Sprite& operator--();

		// modify image
		void setColor(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255) { m_image.setColor(red, green, blue); }
		void setAlpha(Uint8 alpha) { m_image.setAlpha(alpha); }
		//flipping stuff
		void flipVer() { m_image.flipVer(); }
		void flipHor() { m_image.flipHor(); }
		bool isFlippedVer()	{ return m_image.isFlippedVer(); }
		bool isFlippedHor() { return m_image.isFlippedHor(); }

		//angle stuff
		void angle(double angle) { m_image.angle(angle); }
		double angle()	{ return m_image.angle(); }

		int curFrame()	{ return m_cur_frame; }
		int totalFrames() { return m_num_frames; }

		void destWidth(int width) { m_dest_width = width; }
		void destHeight(int height) { m_dest_height = height; }
		int destWidth()	{ return m_dest_width; }
		int destHeight() { return m_dest_height; }

		friend class Graphics;

	private:
		Image m_image;
		Rect * m_rect;
		int m_num_frames;	// Total number of frames
		int m_cur_frame;		// Current frame count, 0 is first frame
		int m_sprite_width;
		int m_sprite_height;

		int m_dest_width;	// May remove these, not very important
		int m_dest_height;
	};
}