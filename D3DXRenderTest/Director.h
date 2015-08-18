#ifndef __DIRECTOR__
#define __DIRECTOR__
#include "SingleInstance.h"
#include <vector>
#include "GameStep.h"

class Director: public SingleInstance<Director>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(Director);

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;

private:

public:
	

};
#endif