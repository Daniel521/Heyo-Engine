#pragma once

// Heyo Engine

#include "h_heyo.h"
#include "h_Character.h"
#include "h_Level.h"
#include "h_Map.h"

#define HeyoWhile(x) while(Heyo::Engine->loop() && x)
#define HeyoMain HeyoMain
#ifdef HEYODEBUG
// Some short hands
#define game	Heyo::Engine
#define gfx		Heyo::Engine->graphics
#endif