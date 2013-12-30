#include "input.h"

#include "logger.h"
#include "keynames.h"

Input::Input()
{
	m_quit = false;
	m_locked = false;

	resetStates();

	for(unsigned int i = 0; i < s_keyNamesSz; ++i)
	{
		KeyName *kn = s_keyNames + i;
		m_keyNames[kn->name] = kn->sym;
	}
}

void Input::resetStates()
{
	m_quit = false;
	for(unsigned int i = 0; i < SDLK_LAST; ++i)
		m_sdlKeyState[i] = false;
}

void Input::update()
{
	SDL_PumpEvents();
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				m_sdlKeyState[event.key.keysym.sym] = true;
			break;

			case SDL_KEYUP:
				m_sdlKeyState[event.key.keysym.sym] = false;
			break;

			case SDL_QUIT:
				m_quit = true;
			break;
		}
	}
}

void Input::registerAlias(const std::string &alias, const std::string &keyName)
{
	KeyNamesIterator kni = m_keyNames.find(keyName);

	ASSERT(kni != m_keyNames.end(),
	       "Could not register alias '%s' - key '%s' does not exist.", alias.c_str(), keyName.c_str());

	m_keyAliases[alias] = kni->second;
}

KeyID Input::keyID(const std::string &nameOrAlias)
{
	KeyNamesIterator kni = m_keyAliases.find(nameOrAlias);

	if(kni == m_keyAliases.end())
	{
		kni = m_keyNames.find(nameOrAlias);

		ASSERT(kni != m_keyNames.end(),
		       "Could not find key or alias '%s'.", nameOrAlias.c_str());
	}

	return kni->second;
}
