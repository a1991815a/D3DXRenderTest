#ifndef __D3DXRENDERENGINE__
#define __D3DXRENDERENGINE__
#include "RenderEngine.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "D3DXProgram.h"
#include "D3DXVertex.h"

class D3DXRenderEngine: public RenderEngine{
private:
	IDirect3D9*				m_d3pp;
	IDirect3DDevice9*		m_device;
	ID3DXSprite*			m_sprite;
	ID3DXFont*				m_font;

	D3DXMATRIX				m_tMatrix;				//原点转换矩阵
	D3DXMATRIX				m_vMatrix;				//裁剪矩阵
	D3DXMATRIX				m_pMatrix;				//投影矩阵
	D3DXProgram				m_defProgram;			//默认着色器
	D3DXMATRIX				Identify_Matrix;		//单位矩阵

	D3DXProgram*			m_curProgram;			//当前使用的着色器程序
public:
	D3DXRenderEngine();
	~D3DXRenderEngine();

	void setOrthoMatrix(float _width, float _height, float _near, float _far);
	void setLookAtMatrix(
		float pos_x, float pos_y, float pos_z,
		float target_x, float target_y, float target_z,
		float up_x, float up_y, float up_z
		);

	const IDirect3DDevice9* getDevice() const {
		return m_device;
	};

	void LinkProgram();
	void setTransformMatrix(const D3DXMATRIX* matrix);
	void setProgram(D3DXProgram* program);
	void setVertexBuffer(IDirect3DVertexBuffer9* buf);
	void setRenderState(D3DRENDERSTATETYPE State, DWORD val);

	void inputMatrix();



private:
	virtual void init() override;

	inline virtual void loop() override{
		this->render();
	};

	virtual void destroy() override;

	void render();


/*
	友元全局函数
*/
	friend void dxSetOrginalMatrix(const D3DXMATRIX* _matrix);						//原点转换矩阵
	friend void setTransformMatrix(const D3DXMATRIX* _matrix);						//model-to-world转换矩阵设置
	friend void dxSetViewMatrix(
		float _width, float _height,
		float _near, float _far);													//裁剪矩阵
	friend void dxSetProjMatrix(
		float pos_x, float pos_y, float pos_z,
		float target_x, float target_y, float target_z,
		float up_x, float up_y, float up_z);										//投影矩阵
	friend void dxCompileShader(
		const std::string& _file_path,
		ShaderVersion _version,
		D3DXProgram* _program);														//编译着色器
	friend void dxLinkProgram(D3DXProgram* _program);								//连接着色器
	friend void dxSetVertexDeclaration(IDirect3DVertexDeclaration9* decl);			//顶点声明
	friend void dxVertexArray(
		const Vertex* _vertex, 
		size_t _offset,
		size_t _count, 
		IDirect3DVertexBuffer9* _buf);												//传输顶点数据
	friend void dxDrawPrimitive(
		D3DPRIMITIVETYPE _type,
		UINT _offset,
		UINT _count);																//图元绘制
	friend void dxSetRenderState(D3DRENDERSTATETYPE _State, DWORD _val);			//设置渲染状态
	friend void dxSetRenderTarget(
		DWORD _render_index,
		IDirect3DSurface9* _surface);												//设置渲染目标
	friend IDirect3DSurface9* dxGetRenderTarget(DWORD _render_index);				//得到当前渲染表面
	friend IDirect3DDevice9* dxGetDevice();											//得到设备接口
	friend ID3DXSprite* dxGetSprite();												//得到精灵
	friend void dxSetFont(ID3DXFont* font);											//设置当前字体
	friend ID3DXFont* dxGetFont();													//得到当前字体
};

#endif