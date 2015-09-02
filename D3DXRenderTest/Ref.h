#ifndef __REF__
#define __REF__
#include "GBAssert.h"
#include "MemoryPool.h"
#include "MemoryPool/gbMemoryPool.h"
#include "MemoryPoolManager.h"
#include "UtilsHeader.h"

class Ref{
public:
	Ref()
		:referenceCount(0), isAutoRelease(false) 
	{};

	Ref(const Ref& ref)
		:referenceCount(0), isAutoRelease(false)
	{

	}

	virtual ~Ref() {
		GBASSERT(referenceCount == 0);
// #ifdef _DEBUG
// 		OutputDebugStringA("回收引用内存: \n");
// #endif
	};
	inline void autorelease() {
		isAutoRelease = true;
		++referenceCount;
		MemoryPoolManager::getInstance()->getCurrentPool()->push(this);
	};

	inline void release() {
		if (--referenceCount == 0 && isAutoRelease) {
			gbDealloc(this);
		};
	};

	inline void retain() {
		++referenceCount;
	};
	
private:
	size_t referenceCount;
	bool isAutoRelease;
};


#endif