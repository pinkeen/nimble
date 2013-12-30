#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#include <vector>
#include <string>
#include <map>

#include "vector.h"

typedef SDLKey KeyID;

class Input
{
	protected:
		bool m_sdlKeyState[SDLK_LAST];
		bool m_quit;
		bool m_locked;

		std::map<std::string, SDLKey> m_keyNames;
		std::map<std::string, SDLKey> m_keyAliases;

		typedef std::map<std::string, SDLKey>::iterator KeyNamesIterator;

	public:
		Input();

		void update();
		void resetStates();

		inline void lock() { m_locked = true; }
		inline void unlock() { m_locked = false; }

		void registerAlias(const std::string &alias, const std::string &keyName);
		KeyID keyID(const std::string &nameOrAlias);

		inline bool keyState(KeyID id) const { if(m_locked) return false; return m_sdlKeyState[id]; }

		inline void resetKeyState(KeyID id) { m_sdlKeyState[id] = false; }

		inline bool keyStateReset(KeyID id)
		{
			if(m_locked) return false;

			bool v = m_sdlKeyState[id];
			m_sdlKeyState[id] = false;
			return v;
		}

		inline bool keyComboStateReset(KeyID id1, KeyID id2)
		{
			if(m_locked) return false;

			bool v = m_sdlKeyState[id1] && m_sdlKeyState[id2];

			if(v)
			{
				m_sdlKeyState[id1] = false;
				m_sdlKeyState[id2] = false;
			}

			return v;
		}

		inline bool keyComboStateReset(KeyID id1, KeyID id2, KeyID id3)
		{
			if(m_locked) return false;

			bool v = m_sdlKeyState[id1] && m_sdlKeyState[id2] && m_sdlKeyState[id3];

			if(v)
			{
				m_sdlKeyState[id1] = false;
				m_sdlKeyState[id2] = false;
				m_sdlKeyState[id3] = false;
			}

			return v;
		}

		inline bool quit() const { return m_quit; }
};

#endif // INPUT_H
