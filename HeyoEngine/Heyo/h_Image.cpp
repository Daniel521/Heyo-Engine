#include "h_Image.h"
#include "h_Graphics.h"
#include "h_heyo.h"
#include <algorithm>
//#include "..\SDL2\include\SDL_image.h"
#include <SDL_image.h>
#include <iostream>


namespace Heyo {

	void Image::clear()
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

	bool Image::load(const Graphics* graphics, std::string imgAddress) {
		if (graphics == nullptr) {
			std::cout << "Failed to load image: passed in nullptr in graphics parameter!" << std::endl;
			return false;
		}
		m_graphics = graphics;

		if (m_texture != NULL)	clear();

		// If imgAddress == "", then load default white square texture, used for debugging mainly
		if (imgAddress.empty() == true) {
						// SDL_PIXELFORMAT_RGBA8888
						// 32 bits per pixel
			if ((m_surface = SDL_CreateRGBSurface(0, 10, 10, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)) == NULL) {
				std::cout << "Failed to load image: loadedSurface Broke!" << std::endl;
				return false;
			}

			SDL_PixelFormat * fmt;
			fmt = m_surface->format;

			SDL_LockSurface(m_surface);
			SDL_memset(m_surface->pixels, 0xff, m_surface->h * m_surface->pitch);
			SDL_UnlockSurface(m_surface);

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

		// Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(imgAddress.c_str());
		if (loadedSurface == NULL) {
			SDL_Log("Unable to load image %s! SDL_image error: %s\n", imgAddress.c_str(), IMG_GetError());
			return false;
		}
		else {
			// Convert surface to screen format
			m_surface = SDL_ConvertSurface(loadedSurface, m_graphics->m_win_surface->format, NULL);

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

	void Image::flipVer() {
		if (flipped == SDL_FLIP_NONE)
			flipped = SDL_FLIP_VERTICAL;
		else if (flipped == SDL_FLIP_VERTICAL)
			flipped = SDL_FLIP_NONE;
		else if (flipped == SDL_FLIP_HORIZONTAL)
			flipped = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		else
			flipped = SDL_FLIP_HORIZONTAL;

		m_flipped_ver = !m_flipped_ver;
	}

	void Image::flipHor() {
		if (flipped == SDL_FLIP_NONE)
			flipped = SDL_FLIP_HORIZONTAL;
		else if (flipped == SDL_FLIP_VERTICAL)
			flipped = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		else if (flipped == SDL_FLIP_HORIZONTAL)
			flipped = SDL_FLIP_NONE;
		else
			flipped = SDL_FLIP_VERTICAL;

		m_flipped_hor = !m_flipped_hor;
	}

	void Image::setColor(Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetTextureColorMod(m_texture, red, green, blue);
	}

	void Image::setAlpha(Uint8 alpha) {
		SDL_SetTextureAlphaMod(m_texture, alpha);
	}

}