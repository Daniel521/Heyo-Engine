#include "h_Sprite.h"
#include "iostream"
using namespace std;

namespace Heyo {

	Sprite::Sprite() : m_rect(NULL), m_numFrames(0), m_curFrame(0), m_spriteWidth(0), m_spriteHeight(0), m_image(NULL)
	{

	}

	Sprite::Sprite(const Graphics * graphics) : m_rect(NULL), m_numFrames(0), m_curFrame(0), m_spriteWidth(0), m_spriteHeight(0), m_image(graphics)
	{
	}

	Sprite::~Sprite()
	{
		if (m_rect != NULL)
			delete[] m_rect;
	}

	void Sprite::init(Graphics * graphics)
	{
		m_image.m_graphics = graphics;
	}

	bool Sprite::loadSprite(std::string imgAddress, int indiWidth, int indiHeight)
	{
		// Step 1: load image
		if (m_image.loadImage(imgAddress) == false) {
			SDL_Log("%s image did not load.\n", imgAddress.c_str());
			return false;
		}

		// Step 2: initilize all the member variables
		if (indiWidth <= 0 || indiWidth > m_image.getWidth())
		{
			m_spriteWidth = m_image.getWidth();
		}
		else
			m_spriteWidth = indiWidth;

		if (indiHeight <= 0 || indiHeight > m_image.getHeight())
		{
			m_spriteHeight = m_image.getHeight();
		}
		else
			m_spriteHeight = indiHeight;

		int numX = (m_image.getWidth() / m_spriteWidth);
		int numY = (m_image.getHeight() / m_spriteHeight);

		m_numFrames = (numX) * (numY);

		m_rect = new Rect[m_numFrames];

		// Step 3: Fill every rect
		// 1) Every rect will have the same h and w;
		for (int i = 0; i < m_numFrames; i++) {
			m_rect[i].w = m_spriteWidth;
			m_rect[i].h = m_spriteHeight;
		}
		// 2) Now some math to determine position
		int curFrame = 0;
		int yStartPos = 0;
		for (int y = 0; y < numY; y++) {
			int xStartPos = 0;
			for (int x = 0; x < numX; x++) {
				m_rect[curFrame].x = xStartPos;
				m_rect[curFrame].y = yStartPos;
				xStartPos += m_spriteWidth;
				curFrame++;
			}
			yStartPos += m_spriteHeight;
		}

		setdestWidth(m_spriteWidth);
		setdestHeight(m_spriteHeight);

		return true;
	}

	int Sprite::getTotalWidth()
	{
		return m_image.getWidth();
	}

	int Sprite::getTotalHeight()
	{
		return m_image.getHeight();
	}


	int Sprite::getWidth()
	{
		return m_spriteWidth;
	}

	int Sprite::getHeight()
	{
		return m_spriteHeight;
	}

	const Rect & Sprite::getcurRect()
	{
		return m_rect[m_curFrame];
	}

	Sprite & Sprite::operator[](int val)
	{
		swap(val);
		return *this;
	}

	int Sprite::gettotalFrames()
	{
		return m_numFrames;
	}

	void Sprite::setdestWidth(int width)
	{
		m_destWidth = width;
	}

	void Sprite::setdestHeight(int height)
	{
		m_destHeight = height;
	}

	void Sprite::swap(int val)
	{
		if (val < 0 || val > m_numFrames - 1)
			return;
		m_curFrame = val;
	}

	Sprite & Sprite::operator++()
	{
		if (m_curFrame >= m_numFrames - 1)
			m_curFrame = 0;
		else
			m_curFrame++;

		return *this;
	}

	Sprite & Sprite::operator--()
	{
		if (m_curFrame <= 0)
			m_curFrame = m_numFrames - 1;
		else
			m_curFrame++;

		return *this;
	}

	void Sprite::flipVer()
	{
		m_image.flipVer();
	}

	void Sprite::flipHor()
	{
		m_image.flipHor();
	}


}