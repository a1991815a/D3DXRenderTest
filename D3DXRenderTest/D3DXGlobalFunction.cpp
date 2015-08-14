#include "D3DXGlobalFunction.h"
#include "D3DXRenderEngine.h"
#include "D3DXRenderEngine.h"
#include "D3DXProgram.h"

#ifndef _OPENGL

D3DXRenderEngine* D3DXRenderEngineObject::d3dx_engine = nullptr;

#define _d3d_render_engine D3DXRenderEngineObject::d3dx_engine 

void dxSetOrginalMatrix(const D3DXMATRIX* _matrix)
{
	_d3d_render_engine->m_tMatrix = *_matrix;
}

void dxSetTransforMatrix(const D3DXMATRIX* _matrix)
{
	
}

void dxSetViewMatrix(
	float _width, float _height,
	float _near, float _far
	)
{
	D3DXMatrixOrthoRH(&_d3d_render_engine->m_vMatrix, 
		_width, _height, _near, _far);
}

void dxSetProjMatrix(
	float pos_x, float pos_y, float pos_z,
	float target_x, float target_y, float target_z,
	float up_x, float up_y, float up_z
	)
{
	D3DXMatrixLookAtRH(
		&_d3d_render_engine->m_pMatrix,
		&D3DXVECTOR3(pos_x, pos_y, pos_z),
		&D3DXVECTOR3(target_x, target_y, target_z),
		&D3DXVECTOR3(up_x, up_y, up_z)
		);
}

void dxCompileShader(
	const std::string& _file_path, 
	ShaderVersion _version, 
	D3DXProgram* _program
	)
{
	D3DXProgram::createShaderFromFile(_file_path, _version, _program);
}

void dxLinkProgram(D3DXProgram* _program)
{
	_d3d_render_engine->setProgram(_program);
}

void dxSetVertexDeclaration(IDirect3DVertexDeclaration9* decl)
{
	_d3d_render_engine->m_device->SetVertexDeclaration(decl);
}

void dxVertexArray(
	const Vertex* _vertex, 
	size_t _offset, 
	size_t _count, 
	IDirect3DVertexBuffer9* _buf)
{
	void* data_ptr = nullptr;
	D3DVERTEXBUFFER_DESC buf_desc;
	_buf->GetDesc(&buf_desc);
	_buf->Lock(_offset, _vertex->getSize() * _count, &data_ptr, 0);
	memcpy_s(data_ptr, buf_desc.Size, _vertex, _vertex->getSize() * _count);
	_buf->Unlock();
	_d3d_render_engine->m_device->SetStreamSource(0, _buf, _offset, _vertex->getSize());
}

void dxDrawPrimitive(D3DPRIMITIVETYPE _type, UINT _offset, UINT _count)
{
	_d3d_render_engine->m_device->DrawPrimitive(_type, _offset, _count);
}

void dxSetRenderState(D3DRENDERSTATETYPE _State, DWORD _val)
{
	_d3d_render_engine->m_device->SetRenderState(_State, _val);
}

void dxSetRenderTarget(
	DWORD _render_index,
	IDirect3DSurface9* _surface
	)
{
	_d3d_render_engine->m_device->SetRenderTarget(_render_index, _surface);
}

IDirect3DSurface9* dxGetRenderSurface(DWORD _render_index)
{
	IDirect3DSurface9* render_surface = nullptr;
	_d3d_render_engine->m_device->GetRenderTarget(_render_index, &render_surface);
	return render_surface;
}

#endif // !_OPENGL

