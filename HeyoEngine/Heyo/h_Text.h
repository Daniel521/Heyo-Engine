#pragma once
//#include "..\SDL2\include\SDL_ttf.h"
#include <SDL_ttf.h>
#include <string>

using std::string;


namespace Heyo {
	typedef SDL_Color Color;

	class Graphics;

	class Text
	{
	private:
		TTF_Font * m_font;
		string m_fontName;
		SDL_Texture * m_texture;
		Color m_color;
		int m_width;
		int m_height;

		Uint8 m_alpha;
		SDL_RendererFlip flipped;
		bool m_flippedHor;
		bool m_flippedVer;

		double m_angle;

		Graphics const * m_graphics;

		void clear();

	public:
		Text(const Graphics * graphics);
		~Text();

		bool loadFont(std::string fontaddress);
		bool setText(std::string text, Color m_color = { 255,255,255 });


		//void setColor(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);
		void setAlpha(Uint8 value = 255);

		//flipping stuff
		void flipVer();
		void flipHor();

		//flip check
		bool isFlippedVer();
		bool isFlippedHor();

		//angle stuff
		void setAngle(double angle);
		double getAngle();

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }
		Color getColor() { return m_color; }
		Uint8 getAlpha() { return m_alpha; }


		friend class Graphics;
	};

}