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

void setTransformMatrix(const D3DXMATRIX* _matrix);						//model-to-worldת����������
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
const D3DXProgram* dxGetProgram();										//�õ���ǰ��ɫ��
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
IDirect3DSurface9* dxGetRenderTarget(DWORD _render_index);				//�õ���ǰ��Ⱦ����
IDirect3DDevice9* dxGetDevice();										//�õ�dx�豸�ӿ�
ID3DXSprite* dxGetSprite();												//�õ�����
ID3DXFont* dxGetFont();													//�õ���ǰ����
void dxSetFont(ID3DXFont* font);										//���õ�ǰ����
void dxDrawText(const std::string& text, 
	int x, int y, 
	DWORD Format,
	D3DCOLOR Color
	);																	//��������
ID3DXFont* dxCreateFont(
	size_t Width,
	int Height,
	size_t Weight,
	size_t MipmapLevel,
	bool Italic,
	DWORD Charset,
	DWORD OutputPrecision,
	DWORD Quality,
	DWORD PitchAndFamily,
	const char* FontName
	);																	//��������



#endif

#endif