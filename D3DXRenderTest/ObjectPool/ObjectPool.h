#ifndef __OBJECTPOOL__
#define __OBJECTPOOL__
#include <vector>

#ifdef _DEBUG
#include <windows.h>
#endif

#ifndef MBYTE
#define MBYTE unsigned char
#endif

template<typename _dTy>
class ObjectPool{
private:
	struct MemoryChunk{
		MemoryChunk(size_t size);
		~MemoryChunk();
		MBYTE* start;
		MBYTE* end;
		void alloc(size_t size);
		void dealloc();
		bool inChunk(_dTy* pObj) const;
	};

public:
	ObjectPool();
	~ObjectPool();

	void resize(size_t size);


	_dTy* alloc();
	void dealloc(_dTy* pObj);

	size_t size() const;

private:
	bool inPool(_dTy* pObj) const;
private:
	std::vector<_dTy*> m_objPool;				//对象池
	std::vector<MemoryChunk*> m_memoryPool;		//内存块
};


template<typename _dTy>
ObjectPool<_dTy>::MemoryChunk::MemoryChunk(size_t size)
	:start(nullptr), end(nullptr)
{
	alloc(size);

}


template<typename _dTy>
void ObjectPool<_dTy>::MemoryChunk::dealloc()
{
	if(start)
		free(start);
	start = end = nullptr;
#ifdef _DEBUG
	char debug_text[64] = { 0 };
	sprintf_s(debug_text, "释放内存: 0x%x  Size: \n",(size_t)start);
	OutputDebugStringA(debug_text);
#endif
}

template<typename _dTy>
void ObjectPool<_dTy>::MemoryChunk::alloc( size_t size )
{
	if(start)
		throw std::runtime_error("The Chunk has been alloced!");
	start = (MBYTE*)malloc(size);
	end = start + size;
#ifdef _DEBUG
	char debug_text[64] = { 0 };
	sprintf_s(debug_text, "分配内存: 0x%x  Size: %d \n",(size_t)start, size);
	OutputDebugStringA(debug_text);
#endif
}


template<typename _dTy>
ObjectPool<_dTy>::MemoryChunk::~MemoryChunk()
{
	dealloc();
}

template<typename _dTy>
bool ObjectPool<_dTy>::MemoryChunk::inChunk( _dTy* pObj ) const
{
	return ((MBYTE*)pObj > start && (MBYTE*)pObj <= end);
}




template<typename _dTy>
bool ObjectPool<_dTy>::inPool( _dTy* pObj ) const
{
	for (size_t i = 0; i < m_memoryPool.size(); ++i)
		if(m_memoryPool.at(i)->inChunk(pObj))
			return true;
	return false;
}

template<typename _dTy>
size_t ObjectPool<_dTy>::size() const
{
	return m_objPool.size();
}

template<typename _dTy>
void ObjectPool<_dTy>::dealloc( _dTy* pObj )
{
	if(!inPool(pObj))
		throw std::runtime_error("The Object is not in this ObjectPool!");
	MBYTE* pByte = (MBYTE*)pObj;
	--pByte;
	*pByte = 0;
	pObj->~_dTy();
	m_objPool.push_back(pObj);

#ifdef _DEBUG
	char debug_text[64] = { 0 };
	sprintf_s(debug_text, "回收对象: 0x%x  Size: %d \n",(size_t)pObj, sizeof(_dTy));
	OutputDebugStringA(debug_text);
#endif
}

template<typename _dTy>
_dTy* ObjectPool<_dTy>::alloc()
{
	if(this->size() == 0)
		throw std::runtime_error("The ObjectPool is not enough!");
	_dTy* pObj = m_objPool.back();
	m_objPool.pop_back();
	MBYTE* pByte = (MBYTE*)pObj;
	--pByte;
	*pByte = 1;
	new (pObj) _dTy;

#ifdef _DEBUG
	char debug_text[64] = { 0 };
	sprintf_s(debug_text, "分配对象: 0x%x  Size: %d \n",(size_t)pObj, sizeof(_dTy));
	OutputDebugStringA(debug_text);
#endif

	return pObj;
}

template<typename _dTy>
void ObjectPool<_dTy>::resize( size_t size )
{
	int alloc_size = size - this->size();
	if(alloc_size > 0)
	{
		m_objPool.reserve(size);
		size_t bSize = (sizeof(_dTy) + 1) * alloc_size;
		MemoryChunk* chunk = new MemoryChunk(bSize);
		memset(chunk->start, 0, bSize);
		m_memoryPool.push_back(chunk);
		MBYTE* pObj = chunk->start + 1;
		for (int i = 0; i < alloc_size; ++i,pObj += sizeof(_dTy) + 1)
			m_objPool.push_back((_dTy*)pObj);
	}
}

template<typename _dTy>
ObjectPool<_dTy>::~ObjectPool()
{
	for (size_t i = 0; i < m_memoryPool.size(); ++i)
	{
		size_t pSize = sizeof(_dTy) + 1;
		MemoryChunk* chunk = m_memoryPool.at(i);
		size_t eleSize = (chunk->end - chunk->start) / pSize;
		MBYTE* pByte = chunk->start;
		for (size_t j = 0; j < eleSize; ++j)
		{
			if(*pByte == 1)
			{
				_dTy* pObj = (_dTy*)(pByte + 1);
				pObj->~_dTy();
			}
#ifdef _DEBUG
			else if (*pByte > 1) {
				if (MessageBoxA(nullptr, "~ObjectPool(): ObjectPool flag is error!", "ObjectPool Error", MB_OK) == IDOK)
					exit(0);
			}
#endif
			/*在析构函数中跑出异常时非常危险的！
			else if(*pByte > 1){
				throw std::runtime_error("ObjectPool flag is error!");
			}*/
			pByte += pSize;
		}
		delete chunk;
	}
		
	m_objPool.clear();
	m_memoryPool.clear();
}

template<typename _dTy>
ObjectPool<_dTy>::ObjectPool()
{

}

#ifdef MBYTE
#undef MBYTE
#endif


#endif