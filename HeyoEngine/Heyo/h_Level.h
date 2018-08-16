#pragma once

/*******************************************************
//		Level Class
//	This class will deal with the levels for a platform.
// ths class will use character and map class
********************************************************/
#include "h_Map.h"
#include "h_Character.h"


namespace Heyo_Platform
{

	class Level
	{
	private:
		Map map;
		Character character;
	public:
		Level();
		~Level();

		// Update game logic
		void update();

		// Draw sprites
		void draw();

	};
}