#include "Serialization.h"

GString Serialization::serialization(bool _bool)
{
	GString serial;
	if (_bool)
		serial += 1;
	else
		serial += 0;
	return serial;
}
