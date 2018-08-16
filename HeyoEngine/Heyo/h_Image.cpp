#include "h_Image.h"
#include "h_Graphics.h"
#include "h_heyo.h"
//#include "..\SDL2\include\SDL_image.h"
#include <SDL_image.h>

namespace Heyo {

	Image::Image(const Graphics * graphics) : m_surface(NULL), m_texture(NULL), m_width(0), m_height(0), m_graphics(graphics), m_flippedVer(false), m_flippedHor(false), m_angle(0.0)
	{

	}

	Image::~Image()	// Done?
	{
		clear();
	}

	void Image::clear()	// Done?
	{
		if (m_surface != NULL) {
			SDL_FreeSurface(m_surface);
			m_surface = NULL;
		}
		if (m_texture != NULL) {
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;
		}
		m_width = 0;
		m_height = 0;
		m_rect = { 0,0,0,0 };
	}

	bool Image::loadImage(std::string imgAddress)
	{
		if (m_surface != NULL)
			clear();

		// Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(imgAddress.c_str());
		if (loadedSurface == NULL) {
			SDL_Log("Unable to load image %s! SDL_image error: %s\n", imgAddress.c_str(), IMG_GetError());
			return false;
		}
		else {
			// Convert surface to screen format
			m_surface = SDL_ConvertSurface(loadedSurface, m_graphics->m_winSurface->format, NULL);

			// Get rid of old loaded surfaces
			SDL_FreeSurface(loadedSurface);
			SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB(m_surface->format, 0, 0xFF, 0xFF));

			// Convert surface to texture
			m_texture = SDL_CreateTextureFromSurface(m_graphics->m_renderer, m_surface);

			// Misc information
			m_width = m_surface->w;
			m_height = m_surface->h;

			m_rect.x = 0;
			m_rect.y = 0;
			m_rect.h = m_height;
			m_rect.w = m_width;

			if (m_surface != NULL) {
				SDL_FreeSurface(m_surface);
				m_surface = NULL;
			}

			return true;
		}
	}

	const int & Image::getWidth()
	{
		return m_width;
	}

	const int & Image::getHeight()
	{
		return m_height;
	}

	const Rect & Image::getRect()
	{
		return m_rect;
	}

	void Image::flipVer()
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

	void Image::flipHor()
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

	bool Image::isFlippedVer()
	{
		return m_flippedVer;
	}

	bool Image::isFlippedHor()
	{
		return m_flippedHor;
	}

	void Image::setAngle(double angle)
	{
		m_angle = angle;
	}

	double Image::getAngle()
	{
		return m_angle;
	}

	void Image::setColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod(m_texture, red, green, blue);
	}

	void Image::setAlpha(Uint8 alpha)
	{
		SDL_SetTextureAlphaMod(m_texture, alpha);
	}

}