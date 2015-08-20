#ifndef __D3DXRENDERENGINE__
#define __D3DXRENDERENGINE__
#include "RenderEngine.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "D3DXProgram.h"
#include "D3DXVertex.h"
#include <set>
#include "Node.h"
#include <xstddef>

template<typename _vTy>
struct Node_less
	: public std::binary_function<_vTy, _vTy, bool> {
	bool operator()(const _vTy& _Left, const _vTy& _Right) const
	{	// apply operator< to operands
		return (_Left->getGlobal() < _Right->getGlobal());
	}
};

class D3DXRenderEngine: public RenderEngine{
	typedef std::vector<Node*>					  local_vector;
	typedef std::multiset<Node*, Node_less<Node*>> global_set;
private:
	IDirect3D9*				m_d3pp;
	IDirect3DDevice9*		m_device;
	ID3DXSprite*			m_sprite;
	ID3DXFont*				m_font;

	D3DXMATRIX				m_tMatrix;				//ԭ��ת������
	D3DXMATRIX				m_vMatrix;				//�ü�����
	D3DXMATRIX				m_pMatrix;				//ͶӰ����
	D3DXProgram				m_defProgram;			//Ĭ����ɫ��
	D3DXMATRIX				Identify_Matrix;		//��λ����

	D3DXProgram*			m_curProgram;			//��ǰʹ�õ���ɫ������

	local_vector			m_localList;			//������ȾĿ��
	global_set				m_globalList;			//ȫ����ȾĿ��
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
	virtual bool init(HWND hwnd) override;

	virtual void loop() override{
		this->render();
	};

	virtual void destroy() override;

	void render();
	void render_pre();
	void render_local();
	void render_next();

/*
	��Ԫȫ�ֺ���
*/
	friend void dxSetOrginalMatrix(const D3DXMATRIX* _matrix);						//ԭ��ת������
	friend void setTransformMatrix(const D3DXMATRIX* _matrix);						//model-to-worldת����������
	friend void dxSetViewMatrix(
		float _width, float _height,
		float _near, float _far);													//�ü�����
	friend void dxSetProjMatrix(
		float pos_x, float pos_y, float pos_z,
		float target_x, float target_y, float target_z,
		float up_x, float up_y, float up_z);										//ͶӰ����
	friend void dxCompileShader(
		const std::string& _file_path,
		ShaderVersion _version,
		D3DXProgram* _program);														//������ɫ��
	friend void dxLinkProgram(D3DXProgram* _program);								//������ɫ��
	friend D3DXProgram* dxGetProgram();
	friend void dxSetVertexDeclaration(IDirect3DVertexDeclaration9* decl);			//��������
	friend void dxVertexArray(
		const Vertex* _vertex, 
		size_t _offset,
		size_t _count, 
		IDirect3DVertexBuffer9* _buf);												//���䶥������
	friend void dxDrawPrimitive(
		D3DPRIMITIVETYPE _type,
		UINT _offset,
		UINT _count);																//ͼԪ����
	friend void dxSetRenderState(D3DRENDERSTATETYPE _State, DWORD _val);			//������Ⱦ״̬
	friend void dxSetRenderTarget(
		DWORD _render_index,
		IDirect3DSurface9* _surface);												//������ȾĿ��
	friend IDirect3DSurface9* dxGetRenderTarget(DWORD _render_index);				//�õ���ǰ��Ⱦ����
	friend IDirect3DDevice9* dxGetDevice();											//�õ��豸�ӿ�
	friend ID3DXSprite* dxGetSprite();												//�õ�����
	friend void dxSetFont(ID3DXFont* font);											//���õ�ǰ����
	friend ID3DXFont* dxGetFont();													//�õ���ǰ����
	friend void dxPushQuadCommand(Node* node);										//������Ⱦ����
	friend const D3DXMATRIX* dxGetIndentityMatrix();								//�õ���λ����
};

#endif