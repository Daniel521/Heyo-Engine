#pragma once

//#include "..\SDL2\include\SDL.h"
//#include "..\SDL2\include\SDL_image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "h_Image.h"
#include "h_Sprite.h"
#include "h_Text.h"


namespace Heyo {

	class Sprite;

	typedef Uint32 Uint32;

	class Graphics
	{
	public:
		int const * SCREEN_WIDTH;
		int const * SCREEN_HEIGHT;
		const std::string m_title;

		friend class Image;
		friend class Text;

	private:
		SDL_Window * m_window;
		SDL_Renderer * m_renderer;
		SDL_Texture * m_texture;
		SDL_Surface * m_winSurface;

	public:
		Graphics();
		Graphics(int width, int height, std::string title);
		~Graphics();

		// BUGGY! Does not work well. Avoid!
		bool changeScreenSize(int width = 600, int height = 400);

		// Clears the renderer
		void clear();

		//simple drawing shapes (part of update i guess)
		
		//Draws a simple square
		void drawRect(Rect & destin, bool fill = true, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void drawRect(int w, int h, int x, int y, bool fill = true, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		
		//Draws a simple pixel
		void drawPixel(int x, int y, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);

		void update(Sprite & p_sprite, int x, int y);
		void update(Sprite & p_sprite, Rect & destin);
		void update(Sprite & p_sprite, Point & destin);
		void update(Text & p_text, Rect & destin, std::string text, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		// update text, point specifies the center of the text
		void update(Text & p_text, Point & center, std::string text, double source_mult = 1.0, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void update(Image & p_image, Rect & destin);
		void update(Image & p_image, Rect & source, Rect & destin);
		void update(Image & p_image, Point & destin);

		int getScreenWidth();
		int getScreenHeight();

		void render();

	private:
		bool init();
		void close();

	};

}