#pragma once

//#include "..\SDL2\include\SDL.h"
#include <SDL.h>
#include <string>

// TODO:
//		1. Add more more image type support, right now it's only png



namespace Heyo {
	
	class Graphics;

	typedef SDL_Rect Rect;
	typedef SDL_Point Point;
	typedef SDL_Point Coord;

	// Image class, used to load images into Heyo engine, includes a few tools to manipulate the image.
	class Image
	{
	public:
		//enum type {
		//	UNKNOWN = 0,
		//	BMP = 1,
		//	PNG = 2
		//};

	private:
		SDL_Surface * m_surface;
		SDL_Texture * m_texture;
		Rect m_rect;
		int m_width;
		int m_height;

		SDL_RendererFlip flipped;
		bool m_flippedHor;
		bool m_flippedVer;

		double m_angle;

		const Graphics * m_graphics;

	private:
		void clear();

	public:
		Image(const Graphics * graphics);
		~Image();
		bool loadImage(std::string imgAddress);
		const int & getWidth();
		const int & getHeight();
		const Rect & getRect();

		//flipping stuff
		void flipVer();
		void flipHor();

		//flip check
		bool isFlippedVer();
		bool isFlippedHor();

		//angle stuff
		void setAngle(double angle);
		double getAngle();

		// Changes how percentage of a color on an image
		void setColor(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void setAlpha(Uint8 alpha = 255);


		friend class Sprite;
		friend class Graphics;
	};

}