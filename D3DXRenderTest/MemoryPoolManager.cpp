#include "MemoryPoolManager.h"

MemoryPoolManager::MemoryPoolManager()
{}

MemoryPoolManager::~MemoryPoolManager()
{
	delete m_poolList.front();
	m_poolList.clear();
}

void MemoryPoolManager::push(MemoryPool* pool)
{
	m_poolList.push_back(pool);
}

void MemoryPoolManager::pop()
{
	m_poolList.pop_back();
}

MemoryPool* MemoryPoolManager::getCurrentPool()
{
	return m_poolList.back();
}

bool MemoryPoolManager::init()
{
	m_poolList.reserve(10);
	new MemoryPool();
	return true;
}

void MemoryPoolManager::loop()
{
	getCurrentPool()->clear();
}

void MemoryPoolManager::destroy()
{
	
}
