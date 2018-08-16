#include "h_Event.h"
#include "h_heyo.h"
#include <iostream>
using namespace std;


namespace Heyo {

	bool processEvent(Events::Event & a_event)		
		/*	Checks to see if there is a new event,
			returns true if there is, false if not*/
	{
		return SDL_PollEvent(&a_event.m_event);
	}

	Events::Event::Event()
	{
	}


	Events::Event::~Event()
	{
	}

	int Events::Event::type() 
	{
		return m_event.type;
	}

	int Events::Event::keyPressed() 
	{
		return m_event.key.keysym.sym;
	}

	bool Events::Event::quit() 
	{

		return m_event.type == QUIT;

	}
	 
	Events::Key::Key() : m_enaSwitch(NULL), m_disSwitch(NULL), m_pressed(false), m_enaTemp(NULL), m_disTemp(NULL)
	{
	}

	Events::Key::~Key()
	{
		if (m_enaTemp != NULL)
		{
			delete  m_enaTemp;
			m_enaTemp = NULL;
			m_enaSwitch = NULL;
		}
		if (m_disTemp != NULL)
		{
			delete	m_disTemp;
			m_disTemp = NULL;
			m_disSwitch = NULL;
		}
	}

	void Events::Key::init(keys key, bool * enaSwitch, bool * disSwitch)
	{
		m_key = key;
		m_pressed = false;
		if (enaSwitch == NULL)
		{
			m_enaTemp = new bool;
			m_enaSwitch = m_enaTemp;
		}
		else
		{
			m_enaSwitch = enaSwitch;
			m_enaTemp = NULL;
		}

		if (disSwitch == NULL)
		{
			m_disTemp = new bool;
			m_disSwitch = m_disTemp;
		}
		else
		{
			m_disSwitch = disSwitch;
			m_disTemp = NULL;
		}
	}

	void Events::Key::enable()
	{
		if (m_pressed == false)
		{
			*m_enaSwitch = true;
			m_pressed = true;
		}
	}

	void Events::Key::disable()
	{
		*m_disSwitch = false;
		m_pressed = false;
	}

	Events::Key & Events::Key::operator=(Key & val)	// double check this. this could be faulty
	{
		if (m_enaTemp != NULL)
		{
			cout << "enaTemp != NULL!" << endl;
			delete  m_enaTemp;
			m_enaTemp = val.m_enaTemp;
		}
		if (m_disTemp != NULL)
		{
			cout << "disTemp != NULL!" << endl;
			delete	m_disTemp;
			m_disTemp = val.m_disTemp;
		}
		m_key = val.m_key;
		m_pressed = val.m_pressed;
		m_enaSwitch = val.m_enaSwitch;
		m_disSwitch = val.m_disSwitch;
		return *this;
	}

	Events::Events() : is_exit(false)
	{
	}

	Events::~Events()
	{
		clear();
		m_event.~Event();
	}

	bool Events::loop()
	{
		if (m_event.type() == QUIT)
		{
			is_exit = true;
			return false;
		}
		if (SDL_PollEvent(&m_event.m_event) != 0)
		{
			for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++)
			{
				if (m_event.keyPressed() == i->m_key)
				{
					if (m_event.type() == key_types::KEYDOWN)
					{
						i->enable();
						return true;
					}
					else if (m_event.type() == key_types::KEYUP)
					{
						i->disable();
						return true;
					}
				}
			}
		}
		return true;
		
	}

	void Events::clear()
	{
		for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++)
		{
			i->~Key();
		}
		m_keylist.clear();
	}

	bool Events::addKey(keys key, bool * enaSwitch, bool * disSwitch)
	{
		Key temp;
		//temp.init(key, enaSwitch, disSwitch);
		//cout << "Size: " << m_keylist.size() << endl;
		for (std::list<Key>::iterator i = m_keylist.begin(); i != m_keylist.end(); i++)
		{
			if (key == i->m_key)
			{
				*i = temp;
				i->init(key, enaSwitch, disSwitch);
				return true;
			}
		}
		m_keylist.push_back(temp);
		m_keylist.back().init(key,enaSwitch,disSwitch);
		return false;
	}

	int Events::getSize()
	{
		return static_cast<int>(m_keylist.size());
	}

}