#ifndef __RENDEROBJECT__
#define __RENDEROBJECT__
#include "D3DXProgram.h"
#include "D3DXGlobalFunction.h"

class RenderObject{
public:
	RenderObject() 
		:program(dxGetProgram())
	{};

	virtual ~RenderObject() {};
	virtual void visit() = 0;

	inline void linkProgram() {
		dxLinkProgram(program);
	}
	inline D3DXProgram* getProgram() {
		return program;
	};
	inline void setProgram(D3DXProgram* program) {
		this->program = program;
	}
private:
	D3DXProgram* program;											//×ÅÉ«Æ÷
};
#endif