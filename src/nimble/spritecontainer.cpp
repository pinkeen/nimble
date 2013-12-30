#include "spritecontainer.h"

#include "logger.h"

SpriteContainer::SpriteContainer()
	: m_begin(0), m_size(0)
{
}

SpriteContainer::~SpriteContainer()
{
	freeAll();
}

void SpriteContainer::freeAll()
{
	if(m_begin == 0)
		return;

	Element *e = m_begin;
	Element *next;

	while(e != 0)
	{
		next = e->next;
		delete e->sprite;
		delete e;
		e = next;
	}

	m_size = 0;
	m_begin = 0;
}

void SpriteContainer::addSprite(Sprite *pSprite)
{
	m_size++;

	Element *prev = 0;
	Element *current = m_begin;

	if(current == 0)
	{
		Element *el = new Element;
		el->next = 0;
		el->sprite = pSprite;
		m_begin = el;
		return;
	}

	int layer = pSprite->layer();

	while(current->next && current->sprite->layer() <= layer)
	{
		prev = current;
		current = current->next;
	}

	Element *ne = new Element;
	ne->sprite = pSprite;

	/* if we have to place it before current */
	if(current->sprite->layer() > layer)
	{
		ne->next = current;

		if(prev == 0)
		{
			m_begin = ne;
			return;
		}

		prev->next = ne;

		return;
	}

	ne->next = current->next;
	current->next = ne;
}

SpriteContainer::Iterator::Iterator(SpriteContainer *pContainer)
	: m_pContainer(pContainer), m_next(m_pContainer->m_begin), m_current(0), m_prev(0)
{
}

SpriteContainer::Iterator::Iterator(const Iterator &iter)
	: m_pContainer(iter.m_pContainer), m_next(iter.m_next), m_current(iter.m_current), m_prev(iter.m_prev)
{

}

void SpriteContainer::Iterator::reset()
{
	m_next = m_pContainer->m_begin;
	m_current = 0;
	m_prev = 0;
}
