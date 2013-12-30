/**
 * \file object.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "object.h"

#include "logger.h"

Object::Object()
{
	m_pParent = 0;
}

Object::Object(Object *pParent)
{
	if(pParent == 0)
	{
		m_pParent = 0;
		return;
	}

	pParent->registerChild(this);
}

Object::~Object()
{
	for(ChildrenIterator i = m_children.begin(); i != m_children.end(); ++i)
		delete (*i);
}

void Object::registerChild(Object *pChild)
{
	m_children.push_back(pChild);
}
