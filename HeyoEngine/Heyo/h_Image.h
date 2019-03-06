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

	public:
		Image() : m_surface(nullptr), m_texture(nullptr), m_width(0), m_height(0), m_graphics(nullptr), 
			m_flipped_ver(false), m_flipped_hor(false), m_angle(0.0), flipped(SDL_FLIP_NONE) {};
		~Image() { clear(); }
		bool load(const Graphics * graphics = nullptr, std::string imgAddress = "");
		const int width() { return m_width; }
		const int height() { return m_height; }
		const Rect& rect() { return m_rect; }

		//flipping stuff
		void flipVer();
		void flipHor();

		//flip check
		bool isFlippedVer() { return m_flipped_ver; }
		bool isFlippedHor() { return m_flipped_hor; }

		//angle stuff
		void angle(double angle) { m_angle = angle; }
		const double angle() { return m_angle; }

		// Changes how percentage of a color on an image
		void setColor(Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void setAlpha(Uint8 alpha = 255);


		friend class Sprite;
		friend class Graphics;

	private:
		SDL_Surface * m_surface;
		SDL_Texture * m_texture;
		Rect m_rect;
		int m_width;
		int m_height;

		SDL_RendererFlip flipped;
		bool m_flipped_ver;
		bool m_flipped_hor;

		double m_angle;

		const Graphics * m_graphics;

	private:
		void clear();

	};

}