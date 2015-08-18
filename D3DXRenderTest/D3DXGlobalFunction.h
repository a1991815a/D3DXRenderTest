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

void dxSetOrginalMatrix(const D3DXMATRIX* _matrix);						//原点转换矩阵

void setTransformMatrix(const D3DXMATRIX* _matrix);						//model-to-world转换矩阵设置
void dxSetViewMatrix(
	float _width, float _height, 
	float _near, float _far);											//裁剪矩阵
void dxSetProjMatrix(
	float pos_x, float pos_y, float pos_z,
	float target_x, float target_y, float target_z,
	float up_x, float up_y, float up_z);								//投影矩阵
void dxCompileShader(
	const std::string& _file_path,
	ShaderVersion _version,
	D3DXProgram* _program);												//编译着色器
void dxLinkProgram(D3DXProgram* _program);								//连接着色器
const D3DXProgram* dxGetProgram();										//得到当前着色器
void dxSetVertexDeclaration(IDirect3DVertexDeclaration9* decl);			//顶点声明
void dxVertexArray(
	const Vertex* _vertex, 
	size_t _offset, 
	size_t _count, 
	IDirect3DVertexBuffer9* _buf);										//传输顶点数据
void dxDrawPrimitive(
	D3DPRIMITIVETYPE _type,
	UINT _offset,
	UINT _count);														//图元绘制

void dxSetRenderState(D3DRENDERSTATETYPE _State, DWORD _val);			//设置渲染状态
void dxSetRenderTarget(
	DWORD _render_index, 
	IDirect3DSurface9* _surface);										//设置渲染目标
IDirect3DSurface9* dxGetRenderTarget(DWORD _render_index);				//得到当前渲染表面
IDirect3DDevice9* dxGetDevice();										//得到dx设备接口
ID3DXSprite* dxGetSprite();												//得到精灵
ID3DXFont* dxGetFont();													//得到当前字体
void dxSetFont(ID3DXFont* font);										//设置当前字体
void dxDrawText(const std::string& text, 
	int x, int y, 
	DWORD Format,
	D3DCOLOR Color
	);																	//绘制文字
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
	);																	//创建字体



#endif

#endif