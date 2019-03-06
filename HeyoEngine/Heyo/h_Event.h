#pragma once

//#include "..\SDL2\include\SDL.h"
#include <SDL.h>
#include <list>

namespace Heyo {

	class Event;

	enum keys {
		K_UNKNOWN = 0,

		K_RETURN = '\r',
		K_ESCAPE = '\033',
		K_BACKSPACE = '\b',
		K_TAB = '\t',
		K_SPACE = ' ',
		K_EXCLAIM = '!',
		K_QUOTEDBL = '"',
		K_HASH = '#',
		K_PERCENT = '%',
		K_DOLLAR = '$',
		K_AMPERSAND = '&',
		K_QUOTE = '\'',
		K_LEFTPAREN = '(',
		K_RIGHTPAREN = ')',
		K_ASTERISK = '*',
		K_PLUS = '+',
		K_COMMA = ',',
		K_MINUS = '-',
		K_PERIOD = '.',
		K_SLASH = '/',
		K_0 = '0',
		K_1 = '1',
		K_2 = '2',
		K_3 = '3',
		K_4 = '4',
		K_5 = '5',
		K_6 = '6',
		K_7 = '7',
		K_8 = '8',
		K_9 = '9',
		K_COLON = ':',
		K_SEMICOLON = ';',
		K_LESS = '<',
		K_EQUALS = '=',
		K_GREATER = '>',
		K_QUESTION = '?',
		K_AT = '@',
		/*
		Skip uppercase letters
		*/
		K_LEFTBRACKET = '[',
		K_BACKSLASH = '\\',
		K_RIGHTBRACKET = ']',
		K_CARET = '^',
		K_UNDERSCORE = '_',
		K_BACKQUOTE = '`',
		K_a = 'a',
		K_b = 'b',
		K_c = 'c',
		K_d = 'd',
		K_e = 'e',
		K_f = 'f',
		K_g = 'g',
		K_h = 'h',
		K_i = 'i',
		K_j = 'j',
		K_k = 'k',
		K_l = 'l',
		K_m = 'm',
		K_n = 'n',
		K_o = 'o',
		K_p = 'p',
		K_q = 'q',
		K_r = 'r',
		K_s = 's',
		K_t = 't',
		K_u = 'u',
		K_v = 'v',
		K_w = 'w',
		K_x = 'x',
		K_y = 'y',
		K_z = 'z',

		K_CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

		K_F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
		K_F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
		K_F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
		K_F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
		K_F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
		K_F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
		K_F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
		K_F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
		K_F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
		K_F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
		K_F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
		K_F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

		K_PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
		K_SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
		K_PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
		K_INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
		K_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
		K_PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
		K_DELETE = '\177',
		K_END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
		K_PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
		K_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
		K_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
		K_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
		K_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

		K_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
		K_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
		K_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
		K_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
		K_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
		K_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
		K_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
		K_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
		K_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
		K_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
		K_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
		K_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
		K_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
		K_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
		K_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
		K_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
		K_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

		K_APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
		K_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
		K_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
		K_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
		K_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
		K_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
		K_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
		K_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
		K_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
		K_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
		K_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
		K_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
		K_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
		K_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
		K_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
		K_EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
		K_HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
		K_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
		K_SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
		K_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
		K_AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
		K_UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
		K_CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
		K_COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
		K_PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
		K_FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
		K_MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
		K_VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
		K_VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
		K_KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
		K_KP_EQUALSAS400 =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

		K_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
		K_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
		K_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
		K_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
		K_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
		K_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
		K_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
		K_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
		K_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
		K_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
		K_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
		K_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

		K_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
		K_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
		K_THOUSANDSSEPARATOR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
		K_DECIMALSEPARATOR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
		K_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
		K_CURRENCYSUBUNIT =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
		K_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
		K_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
		K_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
		K_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
		K_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
		K_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
		K_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
		K_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
		K_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
		K_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
		K_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
		K_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
		K_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
		K_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
		K_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
		K_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
		K_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
		K_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
		K_KP_DBLAMPERSAND =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
		K_KP_VERTICALBAR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
		K_KP_DBLVERTICALBAR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
		K_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
		K_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
		K_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
		K_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
		K_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
		K_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
		K_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
		K_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
		K_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
		K_KP_MEMSUBTRACT =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
		K_KP_MEMMULTIPLY =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
		K_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
		K_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
		K_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
		K_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
		K_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
		K_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
		K_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
		K_KP_HEXADECIMAL =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

		K_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
		K_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
		K_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
		K_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
		K_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
		K_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
		K_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
		K_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

		K_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

		K_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
		K_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
		K_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
		K_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
		K_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
		K_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
		K_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
		K_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
		K_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
		K_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
		K_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
		K_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
		K_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
		K_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
		K_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
		K_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
		K_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

		K_BRIGHTNESSDOWN =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
		K_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
		K_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
		K_KBDILLUMTOGGLE =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
		K_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
		K_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
		K_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
		K_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP)
	};
	enum key_types {
		UNKOWN = 0,
		QUIT = SDL_QUIT,
		KEYDOWN = SDL_KEYDOWN,
		KEYUP = SDL_KEYUP
	};

	// this handles all of the events/inputs form the user
	class Events {
	public:
		class Event {
		public:
			Event() = default;
			Uint32 type() { return m_event.type; }
			int keyPressed() { return m_event.key.keysym.sym; }
			bool quit() { return m_event.type == QUIT; }

			friend bool processEvent(Event & a_event);
			friend class Events;
		private:
			SDL_Event m_event;
		};

		class Key {
		public:
			Key() : m_enaSwitch(NULL), m_disSwitch(NULL), m_pressed(false),
				m_enaTemp(NULL), m_disTemp(NULL) {}
			~Key();

			void init(keys key, bool * enaSwitch = NULL, bool * disSwitch = NULL);
			void enable();
			void disable();
			Key& operator=(Key & val);
		public:
			keys m_key;
			bool m_pressed;
			bool * m_enaSwitch;
			bool * m_disSwitch;
			bool * m_enaTemp;
			bool * m_disTemp;
		};

	public:
		Events(): is_exit(false) {}
		~Events();

		// returns true if the quit command has been executed,
		// else returns false to keep going
		bool exit() { return is_exit; }

		// DO NOT CALL THIS FUNCTION UNLESS YOU KNOW WHAT YOU"RE DOING
		// Call the loop function in Heyo::Engine instead of this one
		// this one is left here for debugging, don't touch it please,
		// it will screw you over.
		bool loop();

		void clear();

		// adds a key to the list and specify what variables to tweak when the key is manipulated
		// key : the key, use enum keys
		// enaSwitch : ptr to bool that will turn TRUE when button is presssed
		// disSwitch : ptr to bool that will turn FALSE when button is released
		// disSwitch should be left as null if you don't want to use it
		bool addKey(keys key, bool * enaSwitch, bool * disSwitch = NULL);

		// returns the number of keys
		int size() { return static_cast<int>(m_keylist.size()); }

	private:
		bool is_exit;
		Event m_event;
		std::list<Key> m_keylist;
		//std::vector<int> m_enaScalelist;
	};

	bool processEvent(Events::Event & a_event);
	/*	Checks to see if there is a new event,
	returns true if there is, false if not*/
}