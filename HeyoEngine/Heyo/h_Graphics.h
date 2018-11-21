#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "h_Image.h"
#include "h_Text.h"

/*
	Graphics Class
This class deals with handling all of the graphics on the screen.
*/


namespace Heyo {

	class Sprite;
	typedef Uint32 Uint32;

	class Graphics {
	public:
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;
		const std::string TITLE;
	public:
		// Constructors
		Graphics();
		Graphics(int width, int height, std::string title);
		~Graphics() { close(); }

		// Clears the renderer
		void clear(Uint8 red = 0, Uint8 green = 0, Uint8 blue = 0);

		
		//Draws a simple square
		void drawRect(Rect & destin, bool fill = true, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void drawRect(int w, int h, int x, int y, bool fill = true, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		//Draws a simple pixel
		void drawPixel(int x, int y, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void update(Sprite & p_sprite, int x, int y);
		void update(Sprite & p_sprite, Rect & destin);
		void update(Sprite & p_sprite, Point & destin); 		// be careful when using this method, won't work for characters. will fix later 10/8/18
		void update(Text & p_text, Rect & destin, std::string text, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		// update text, point specifies the center of the text
		void update(Text & p_text, Point & center, std::string text, double source_mult = 1.0, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void update(Text & p_text, int x, int y, std::string text, double source_mult = 1.0, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
		void update(Image & p_image, Rect & destin);
		void update(Image & p_image, Rect & source, Rect & destin);
		void update(Image & p_image, Point & destin);

		int getScreenWidth() { return SCREEN_WIDTH; }
		int getScreenHeight() { return SCREEN_HEIGHT; }

		void render();

		friend class Image;
		friend class Text;

		// BUGGY! Does not work well. Avoid!
		// Changed how screen works, this won't work anymore
		//bool changeScreenSize(int width = 600, int height = 400);

	private:
		bool init();
		void close();

	private:
		SDL_Window * m_window;
		SDL_Renderer * m_renderer;
		SDL_Texture * m_texture;
		SDL_Surface * m_winSurface;

	};

}