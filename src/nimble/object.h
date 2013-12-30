/**
 * \file object.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Object
{
	private:
		typedef std::vector<Object*>::iterator ChildrenIterator;

		std::vector<Object*> m_children;
		void registerChild(Object *pChild);
		Object *m_pParent;

	public:
		Object();
		Object(Object *pParent);

		virtual ~Object();

};

#endif // OBJECT_H
