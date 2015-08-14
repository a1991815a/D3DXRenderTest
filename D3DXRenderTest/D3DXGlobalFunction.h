#ifndef __D3DXGLOBALFUNCTION__
#define __D3DXGLOBALFUNCTION__
#include "D3DXProgram.h"
#include <string>
#include "D3DXVertex.h"

#ifndef _OPENGL
class D3DXRenderEngine;

struct D3DXRenderEngineObject {
public:
	static D3DXRenderEngine* d3dx_engine;
};

void dxSetOrginalMatrix(const D3DXMATRIX* _matrix);						//ԭ��ת������
void dxSetTransforMatrix(const D3DXMATRIX* _matrix);					//model-to-worldת����������
void dxSetViewMatrix(
	float _width, float _height, 
	float _near, float _far);											//�ü�����
void dxSetProjMatrix(
	float pos_x, float pos_y, float pos_z,
	float target_x, float target_y, float target_z,
	float up_x, float up_y, float up_z);								//ͶӰ����
void dxCompileShader(
	const std::string& _file_path,
	ShaderVersion _version,
	D3DXProgram* _program);												//������ɫ��
void dxLinkProgram(D3DXProgram* _program);								//������ɫ��
void dxSetVertexDeclaration(IDirect3DVertexDeclaration9* decl);			//��������
void dxVertexArray(
	const Vertex* _vertex, 
	size_t _offset, 
	size_t _count, 
	IDirect3DVertexBuffer9* _buf);										//���䶥������
void dxDrawPrimitive(
	D3DPRIMITIVETYPE _type,
	UINT _offset,
	UINT _count);														//ͼԪ����

void dxSetRenderState(D3DRENDERSTATETYPE _State, DWORD _val);			//������Ⱦ״̬
void dxSetRenderTarget(
	DWORD _render_index, 
	IDirect3DSurface9* _surface);										//������ȾĿ��
IDirect3DSurface9* dxGetRenderSurface(DWORD _render_index);				//�õ���ǰ��Ⱦ����
IDirect3DDevice9* dxGetDevice();										//�õ�dx�豸�ӿ�

#endif

#endif