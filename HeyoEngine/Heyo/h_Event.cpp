#include "h_Event.h"
#include "h_heyo.h"
#include <iostream>


namespace Heyo {
	bool processEvent(Events::Event & a_event) { return SDL_PollEvent(&a_event.m_event); }

	Events::Key::~Key() {
		if (m_enaTemp != NULL) {
			delete  m_enaTemp;
			m_enaTemp = NULL;
			m_enaSwitch = NULL;
		}
		if (m_disTemp != NULL) {
			delete	m_disTemp;
			m_disTemp = NULL;
			m_disSwitch = NULL;
		}
	}

	// 3/5/2019 : Need to check if m_enaTemp did not already equal a new bool, if they already did, then i gotta delete them
	void Events::Key::init(keys key, bool * enaSwitch, bool * disSwitch) {
		m_key = key;
		m_pressed = false;
		if (enaSwitch == NULL) {
			m_enaTemp = new bool;
			m_enaSwitch = m_enaTemp;
		}
		else {
			m_enaSwitch = enaSwitch;
			m_enaTemp = NULL;
		}

		if (disSwitch == NULL) {
			m_disTemp = new bool;
			m_disSwitch = m_disTemp;
		}
		else {
			m_disSwitch = disSwitch;
			m_disTemp = NULL;
		}
	}

	void Events::Key::enable() {
		if (m_pressed == false) {
			*m_enaSwitch = true;
			m_pressed = true;
		}
	}

	void Events::Key::disable() {
		*m_disSwitch = false;
		m_pressed = false;
	}

	// double check this. this could be faulty
	Events::Key& Events::Key::operator=(Key & val) {
		if (m_enaTemp != NULL) {
			std::cout << "enaTemp != NULL!" << std::endl;
			delete  m_enaTemp;
			m_enaTemp = val.m_enaTemp;
		}
		if (m_disTemp != NULL) {
			std::cout << "disTemp != NULL!" << std::endl;
			delete	m_disTemp;
			m_disTemp = val.m_disTemp;
		}
		m_key = val.m_key;
		m_pressed = val.m_pressed;
		m_enaSwitch = val.m_enaSwitch;
		m_disSwitch = val.m_disSwitch;
		return *this;
	}

	Events::~Events() {
		clear();
		m_event.~Event();
	}

	bool Events::loop() {
		if (m_event.type() == QUIT) {
			is_exit = true;
			return false;
		}
		int duplicate = K_UNKNOWN;
		int dup_type = key_types::UNKOWN;

		while (SDL_PollEvent(&m_event.m_event) != 0) {
			if (m_event.keyPressed() == duplicate && m_event.type() == dup_type) continue;
			duplicate = m_event.keyPressed();
			dup_type = m_event.type();
			for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++) {
				if (m_event.keyPressed() == i->m_key) {
					if (m_event.type() == key_types::KEYDOWN) {
						i->enable();
						return true;
					}
					else if (m_event.type() == key_types::KEYUP) {
						i->disable();
						return true;
					}
				}
			}
		}
		return true;
		
	}

	void Events::clear() {
		for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++) {
			i->~Key();
		}
		m_keylist.clear();
	}

	bool Events::addKey(keys key, bool * enaSwitch, bool * disSwitch) {
		Key temp;
		for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++) {
			if (key == i->m_key) {
				*i = temp;
				i->init(key, enaSwitch, disSwitch);
				return true;
			}
		}
		m_keylist.push_back(temp);
		m_keylist.back().init(key,enaSwitch,disSwitch);
		return false;
	}

}