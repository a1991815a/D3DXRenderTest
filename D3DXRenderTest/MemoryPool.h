#ifndef __MEMORYPOOL__
#define __MEMORYPOOL__
#include <vector>

class Ref;

class MemoryPool{
public:
	MemoryPool();
	~MemoryPool();
	void clear();
	void push(Ref* ref);
private:
	std::vector<Ref*> m_refList;
};
#endif