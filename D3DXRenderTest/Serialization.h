#ifndef __SERIALIZATION__
#define __SERIALIZATION__
#include "UtilsHeader.h"

//���л��ӿ�
class Serialization{
protected:
	virtual Value serialization() = 0;
	static GString serialization(bool _bool);

};

#endif