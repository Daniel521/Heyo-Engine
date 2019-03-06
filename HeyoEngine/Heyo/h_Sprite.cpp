#include "h_Sprite.h"
#include "iostream"
using namespace std;

namespace Heyo {

	bool Sprite::load(const Graphics* graphics, std::string imgAddress, int indiWidth, int indiHeight) {
		if (graphics == nullptr) {
			std::cout << "Failed to load sprite: passed in nullptr in graphics parameter." << std::endl;
			return false;
		}

		// Step 1: load image
		if (m_image.load(graphics,imgAddress) == false) {
			SDL_Log("%s image did not load.\n", imgAddress.c_str());
			return false;
		}

		// Step 2: initilize all the member variables
		if (indiWidth <= 0 || indiWidth > m_image.width())
			m_sprite_width = m_image.width();
		else
			m_sprite_width = indiWidth;

		if (indiHeight <= 0 || indiHeight > m_image.height())
			m_sprite_height = m_image.height();
		else
			m_sprite_height = indiHeight;

		int numX = (m_image.width() / m_sprite_width);
		int numY = (m_image.height() / m_sprite_height);

		m_num_frames = (numX) * (numY);

		m_rect = new Rect[m_num_frames];

		// Step 3: Fill every rect
		// 1) Every rect will have the same h and w;
		for (int i = 0; i < m_num_frames; i++) {
			m_rect[i].w = m_sprite_width;
			m_rect[i].h = m_sprite_height;
		}
		// 2) Now some math to determine position
		int curFrame = 0;
		int yStartPos = 0;
		for (int y = 0; y < numY; y++) {
			int xStartPos = 0;
			for (int x = 0; x < numX; x++) {
				m_rect[curFrame].x = xStartPos;
				m_rect[curFrame].y = yStartPos;
				xStartPos += m_sprite_width;
				curFrame++;
			}
			yStartPos += m_sprite_height;
		}

		destWidth(m_sprite_width);
		destHeight(m_sprite_height);

		return true;
	}

	Sprite& Sprite::operator[](int val) {
		swap(val);
		return *this;
	}

	void Sprite::swap(int val) {
		if (val < 0 || val > m_num_frames - 1)
			return;
		m_cur_frame = val;
	}

	Sprite& Sprite::operator++() {
		if (m_cur_frame >= m_num_frames - 1)
			m_cur_frame = 0;
		else
			m_cur_frame++;

		return *this;
	}

	Sprite& Sprite::operator--() {
		if (m_cur_frame <= 0)
			m_cur_frame = m_num_frames - 1;
		else
			m_cur_frame++;

		return *this;
	}
}