#include "h_Text.h"
#include "h_Graphics.h"
#include "h_heyo.h"

namespace Heyo {

	Text::Text(const Graphics * graphics) : m_font(NULL), m_texture(NULL), m_width(0), m_height(0), m_color({ 255,255,255 }), m_graphics(graphics), m_alpha(255)
	{

	}


	Text::~Text()
	{
		if (m_font != NULL)
			TTF_CloseFont(m_font);
		m_font = NULL;
		clear();
	}

	bool Text::loadFont(std::string fontaddress)
	{
		if (m_font != NULL)
		{
			TTF_CloseFont(m_font);
			clear();
		}

		m_font = TTF_OpenFont(fontaddress.c_str(), 28);
		if (m_font == NULL)
		{
			SDL_Log("Failed to load font %s, ", fontaddress);
			SDL_Log("error: %s\n", TTF_GetError());
			return false;
		}
		m_fontName = fontaddress;
		return true;
	}

	bool Text::setText(std::string text, Color m_color)
	{
		SDL_Surface * surface = NULL;

		if (m_texture != NULL)
			clear();

		surface = TTF_RenderText_Solid(m_font, text.c_str(), m_color);
		if (surface == NULL)
		{
			SDL_Log("Unable to render text surface! SDL_ttf error: %s\n", TTF_GetError());
			return false;
		}
		else
		{
			m_texture = SDL_CreateTextureFromSurface(m_graphics->m_renderer, surface);
			SDL_SetTextureAlphaMod(m_texture, m_alpha);

			m_width = surface->w;
			m_height = surface->h;

			SDL_FreeSurface(surface);
			surface = NULL;
		}

		return true;
	}

	// Removed for now since I can not find use for it 11/19/17
	//void Text::setColor(Uint8 r, Uint8 g, Uint8 b)
	//{
	//	m_color = { r,g,b };
	//	SDL_SetTextureColorMod(m_texture,r,g,b);
	//}

	void Text::setAlpha(Uint8 value)
	{
		m_alpha = value;
	}

	void Text::clear()
	{
		if (m_texture != NULL) {
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;
		}
		m_width = 0;
		m_height = 0;
	}

	void Text::flipVer()
	{
		if (flipped == SDL_FLIP_NONE)
			flipped = SDL_FLIP_VERTICAL;
		else if (flipped == SDL_FLIP_VERTICAL)
			flipped = SDL_FLIP_NONE;
		else if (flipped == SDL_FLIP_HORIZONTAL)
			flipped = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		else
			flipped = SDL_FLIP_HORIZONTAL;

		m_flippedVer = !m_flippedVer;
	}

	void Text::flipHor()
	{
		if (flipped == SDL_FLIP_NONE)
			flipped = SDL_FLIP_HORIZONTAL;
		else if (flipped == SDL_FLIP_VERTICAL)
			flipped = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		else if (flipped == SDL_FLIP_HORIZONTAL)
			flipped = SDL_FLIP_NONE;
		else
			flipped = SDL_FLIP_VERTICAL;

		m_flippedHor = !m_flippedHor;
	}

	bool Text::isFlippedVer()
	{
		return m_flippedVer;
	}

	bool Text::isFlippedHor()
	{
		return m_flippedHor;
	}

	void Text::setAngle(double angle)
	{
		m_angle = angle;
	}

	double Text::getAngle()
	{
		return m_angle;
	}

}