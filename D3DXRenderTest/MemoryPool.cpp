#include "MemoryPool.h"
#include "Ref.h"
#include "MemoryPoolManager.h"

MemoryPool::MemoryPool()
{
	m_refList.reserve(160);
	MemoryPoolManager::getInstance()->push(this);
}

MemoryPool::~MemoryPool()
{
	clear();
	MemoryPoolManager::getInstance()->pop();
}

void MemoryPool::clear()
{
	auto itor = m_refList.begin();
	for (; itor != m_refList.end(); ++itor)
		(*itor)->release();
	m_refList.clear();
}

void MemoryPool::push(Ref* ref)
{
	m_refList.push_back(ref);
}