#ifndef __SERIALIZATION__
#define __SERIALIZATION__
#include "UtilsHeader.h"

//序列化接口
class Serialization{
protected:
	virtual Value serialization() = 0;
	static GString serialization(bool _bool);

};

#endif