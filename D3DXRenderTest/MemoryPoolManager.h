#ifndef __MEMORYPOOLMANAGER__
#define __MEMORYPOOLMANAGER__
#include "SingleInstance.h"
#include <vector>
#include "MemoryPool.h"
#include "GameStep.h"

class MemoryPoolManager: public SingleInstance<MemoryPoolManager>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(MemoryPoolManager);
public:
	void push(MemoryPool* pool);
	void pop();
	MemoryPool* getCurrentPool();

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;

private:
	std::vector<MemoryPool*> m_poolList;
};
#endif
