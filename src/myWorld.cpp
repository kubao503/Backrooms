#include "myWorld.h"

MyBody* MyWorld::CreateBody(const b2BodyDef* def, const Object &object)
{
	b2Assert(IsLocked() == false);
	if (IsLocked())
	{
		return nullptr;
	}

	void* mem = m_blockAllocator.Allocate(sizeof(MyBody));
	MyBody* b = new (mem) MyBody(def, static_cast<b2World*>(this), object);

	// Add to world doubly linked list.
	b->m_prev = nullptr;
	b->m_next = m_bodyList;
	if (m_bodyList)
	{
		m_bodyList->m_prev = b;
	}
	m_bodyList = b;
	++m_bodyCount;

	return b;
}