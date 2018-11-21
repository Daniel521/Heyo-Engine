#include "h_Graphics.h"
#include "h_Image.h"
#include "h_Sprite.h"
#include "h_Text.h"

using namespace std;


namespace Heyo {

	Graphics::Graphics() : SCREEN_WIDTH(600), SCREEN_HEIGHT(400), TITLE(std::string("Heyo::Engine")), m_window(NULL), m_winSurface(NULL), m_renderer(NULL), m_texture(NULL) {
		if (!init()) {
			SDL_Log("Failed to Initiate Heyo Engine: %s", SDL_GetError());
			close();
		}
	}

	Graphics::Graphics(int width, int height, std::string title) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height), TITLE(title), m_window(NULL), m_winSurface(NULL), m_renderer(NULL), m_texture(NULL) {
		if (!init()) {
			SDL_Log("Failed to Initiate Heyo Engine.");
			close();
		}
	}

	// unstable!!!
	//bool Graphics::changeScreenSize(int width, int height)
	//{
	//	if (width <= 0 || height <= 0) {
	//		delete SCREEN_WIDTH;
	//		SCREEN_WIDTH = new int(600);
	//		delete SCREEN_HEIGHT;
	//		SCREEN_HEIGHT = new int(400);
	//	}
	//	else {
	//		delete SCREEN_WIDTH;
	//		SCREEN_WIDTH = new int(width);
	//		delete SCREEN_HEIGHT;
	//		SCREEN_HEIGHT = new int(height);
	//	}
	//	return init();
	//}

	// clears the window to pitch black
	void Graphics::clear(Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
		SDL_RenderClear(m_renderer);
	}

	void Graphics::drawRect(Rect & destin, bool fill, Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
		if (fill)
			SDL_RenderFillRect(m_renderer, &destin);
		else
			SDL_RenderDrawRect(m_renderer, &destin);
	}

	void Graphics::drawRect(int w, int h, int x, int y, bool fill, Uint8 red, Uint8 green, Uint8 blue) {
		Rect temp = { x,y,w,h };
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
		if (fill)
			SDL_RenderFillRect(m_renderer, &temp);
		else
			SDL_RenderDrawRect(m_renderer, &temp);
	}

	void Graphics::drawPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
		SDL_RenderDrawPoint(m_renderer, x, y);
	}


	void Graphics::update(Sprite & p_sprite, int x, int y) {
		Rect temp = { x, y, p_sprite.getdestWidth(), p_sprite.getdestHeight() };
		if (SDL_RenderCopyEx(m_renderer, p_sprite.m_image.m_texture, &p_sprite.getcurRect(), &temp, p_sprite.m_image.getAngle(), NULL, p_sprite.m_image.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	// adds the sprite at the destination
	void Graphics::update(Sprite & p_sprite, Rect & destin) {
		if (SDL_RenderCopyEx(m_renderer, p_sprite.m_image.m_texture, &p_sprite.getcurRect(), &destin, p_sprite.m_image.getAngle(), NULL, p_sprite.m_image.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	void Graphics::update(Sprite & p_sprite, Point & destin) {
		Rect temp = { p_sprite.getcurRect().h, p_sprite.getcurRect().w, destin.x, destin.y };
		if (SDL_RenderCopyEx(m_renderer, p_sprite.m_image.m_texture, &p_sprite.getcurRect(), &temp, p_sprite.m_image.getAngle(), NULL, p_sprite.m_image.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	// adds text to the destination
	void Graphics::update(Text & p_text, Rect & destin, string text, Uint8 red, Uint8 green, Uint8 blue) {
		p_text.setText(text, { 255,blue,green,red });
		if (SDL_RenderCopyEx(m_renderer, p_text.m_texture, NULL, &destin, p_text.getAngle(), NULL, p_text.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	void Graphics::update(Text & p_text, Point & center, string text, double source_mult, Uint8 red, Uint8 green, Uint8 blue) {
		p_text.setText(text, { p_text.getAlpha(),blue,green,red });
		double width = p_text.getWidth() / 2.0;
		double height = p_text.getHeight() / 2.0;
		Rect dest;
		dest.x =  static_cast<int>(center.x - (width)*source_mult);
		dest.w = static_cast<int>(center.x + (width)*source_mult - dest.x);
		dest.y = static_cast<int>(center.y - (height)*source_mult);
		dest.h = static_cast<int>(center.y + (height)*source_mult - dest.y);
		if (SDL_RenderCopyEx(m_renderer, p_text.m_texture, NULL, &dest, p_text.getAngle(), NULL, p_text.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	void Graphics::update(Text & p_text, int x, int y, std::string text, double source_mult, Uint8 red, Uint8 green, Uint8 blue) {
		p_text.setText(text, { p_text.getAlpha(),blue,green,red });
		Rect dest;
		dest.x = x;
		dest.w = static_cast<int>(p_text.getWidth() * source_mult);
		dest.y = y;
		dest.h = static_cast<int>(p_text.getHeight() * source_mult);
		if (SDL_RenderCopyEx(m_renderer, p_text.m_texture, NULL, &dest, p_text.getAngle(), NULL, p_text.flipped) != 0)
			SDL_Log("Sprite did not load: %s", SDL_GetError());
	}

	// adds an image (still sprite) to the destination
	void Graphics::update(Image & p_image, Rect & destin) {
		SDL_RenderCopyEx(m_renderer, p_image.m_texture, NULL, &destin, p_image.getAngle(), NULL, p_image.flipped);
	}

	void Graphics::update(Image & p_image, Rect & source, Rect & destin) {
		SDL_RenderCopyEx(m_renderer, p_image.m_texture, NULL, &destin, p_image.getAngle(), NULL, p_image.flipped);
	}

	void Graphics::update(Image & p_image, Point & destin) {
		Rect temp;
		temp = { p_image.getRect().h, p_image.getRect().w, destin.x, destin.y };

		SDL_RenderCopyEx(m_renderer, p_image.m_texture, NULL, &temp, p_image.getAngle(), NULL, p_image.flipped);
	}
	
	// renders everything to the screen
	void Graphics::render()	{
		SDL_RenderPresent(m_renderer);
	}

	// first function to run, basically makes the window
	bool Graphics::init() {
		close();
		// Make Window
		m_window = SDL_CreateWindow(
			(char*)TITLE.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WindowFlags::SDL_WINDOW_SHOWN
		);

		if (!m_window) {
			SDL_Log("Window failed to create: %s", SDL_GetError());
			return false;
		}
		else {
			// Get window surface
			m_winSurface = SDL_GetWindowSurface(m_window);
			if (m_winSurface == NULL) {
				SDL_Log("Window Surface failed: %s", SDL_GetError());
				return false;
			}
		}

		// Make Renderer
		m_renderer = SDL_CreateRenderer(
			m_window,
			-1,
			SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC
		);

		if (!m_renderer) {
			SDL_Log("Renderer failed to create: %s", SDL_GetError());
			return false;
		}
		// Make Texture
		m_texture = SDL_CreateTexture(
			m_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
		);

		if (!m_texture) {
			SDL_Log("Renderer failed to create: %s", SDL_GetError());
			return false;
		}

		return true;
	}

	// closes everything
	void Graphics::close() {
		if (m_winSurface) {
			SDL_FreeSurface(m_winSurface);
			m_winSurface = NULL;
		}
		if (m_window) {
			SDL_DestroyWindow(m_window);
			m_window = NULL;
		}

		if (m_renderer) {
			SDL_DestroyRenderer(m_renderer);
			m_renderer = NULL;
		}

		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;
		}
	}
}