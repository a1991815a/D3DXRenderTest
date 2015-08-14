#ifndef __GBASSERT__
#define __GBASSERT__
#include <assert.h>

#ifdef _DEBUG
#define GB_ASSERT(cond) assert(cond)
#else
#define GB_ASSERT(cond) 
#endif // !_DEBUG

#define GBASSERT(cond) GB_ASSERT(cond)

#endif