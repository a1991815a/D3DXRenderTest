#ifndef __RENDERREF__
#define __RENDERREF__
#include "D3DXProgram.h"
#include "D3DXGlobalFunction.h"

class RenderRef{
public:
	RenderRef() 
		:program(nullptr)
	{};

	virtual ~RenderRef() {};
	virtual void RenderThis() = 0;

	inline void linkProgram() {
		dxLinkProgram(program);
	}
	inline D3DXProgram* getProgram() {
		return program;
	};
	inline void setProgram(D3DXProgram* program) {
		this->program = program;
	}
	inline D3DXMATRIX* getTransformMatrix() {
		return &mMatrix;
	}
	inline const D3DXMATRIX* getTransformMatrix() const {
		return &mMatrix;
	}
	inline void setMatrix(const D3DXMATRIX* matrix) {
		mMatrix = *matrix;
	}

private:
	D3DXProgram* program;									//着色器
	D3DXMATRIX mMatrix;										//模型矩阵
};
#endif