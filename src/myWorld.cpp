#include "myWorld.h"

std::unique_ptr<b2Body> MyWorld::CreateBody(const b2BodyDef* def, const Object3D &object)
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

	return std::unique_ptr<b2Body>(b);
}