#ifndef SPRITECONTAINER_H
#define SPRITECONTAINER_H

#include "sprite.h"

class SpriteContainer
{
	private:
		struct Element
		{
			Sprite *sprite;
			Element *next;
		};

		typedef struct Element Element;

		Element *m_begin;
		int m_size;

	public:
		SpriteContainer();
		~SpriteContainer();

		void freeAll();
		void addSprite(Sprite *pSprite);
		void remSprite(Sprite *pSprite);

		inline int size() const { return m_size; }

		class Iterator
		{
			private:
				Iterator(SpriteContainer *pContainer);
				friend class SpriteContainer;

			private:
				SpriteContainer *m_pContainer;
				Element *m_next;
				Element *m_current;
				Element *m_prev;
			public:
				Iterator(const Iterator &iter);

				inline bool next()
				{
					m_prev = m_current;
					m_current = m_next;

					if(m_current != 0)
					{
						m_next = m_current->next;
						return true;
					}

					return false;
				}

				inline Sprite *item() { return m_current->sprite; }

				inline void removeItem()
				{
					Element *tmp = m_current;

					if(m_prev == 0)
					{
						m_pContainer->m_begin = m_current->next;
						m_current = 0;
					}
					else
					{
						m_prev->next = m_current->next;
						m_current = m_prev;
					}

					delete tmp->sprite;
					delete tmp;

					m_pContainer->m_size--;
				}

				void reset();

		};

		inline Iterator iterator() { return Iterator(this); }
};

#endif // SPRITECONTAINER_H
