#ifndef __D3DXPROGRAM__
#define __D3DXPROGRAM__
#include "D3DXHeader.h"
#include "UtilsHeader.h"
#include <unordered_map>

enum ShaderVersion{
	VS_2_0,
	PS_2_0
};

enum ShaderTypes {
	D3D_VERTEX_SHADER,
	D3D_PIXEL_SHADER
};

class D3DXProgram{
private:
	IDirect3DVertexShader9* m_vShader;
	IDirect3DPixelShader9* m_fShader;
	ID3DXConstantTable* m_vTable;
	ID3DXConstantTable* m_fTable;
	std::unordered_map<GString, D3DXHANDLE> m_vDataHandle;
	std::unordered_map<GString, D3DXHANDLE> m_fDataHandle;
public:
	D3DXProgram();
	~D3DXProgram();
	void setVShader(IDirect3DVertexShader9* vShader);	//���ö�����ɫ��
	void setFShader(IDirect3DPixelShader9* fShader);	//����Ƭ����ɫ��
	
	IDirect3DVertexShader9* getVShader();				//�õ�������ɫ��
	IDirect3DPixelShader9* getFShader();				//�õ�Ƭ����ɫ��
	ID3DXConstantTable* getTable(ShaderTypes shader_type);					//�õ�������

	void initVTable(const GString& val_name);		//��ʼ�����㳣����
	void initFTable(const GString& val_name);		//��ʼ��Ƭ�γ�����
	D3DXHANDLE getHandle(
		const GString& key, 
		ShaderTypes shader_type);						//�õ��������



	//���ļ�����Shader
	static void createShaderFromFile(
		const GString& file_name,
		ShaderVersion version, 
		D3DXProgram* program);
	//�����ݴ���Shader
	static void createShaderFromData(
		const GString& source,
		ShaderVersion version, 
		D3DXProgram* program);
	//�õ��汾�ַ���
	static const char* getVersion(ShaderVersion version);


/*
	��������������
*/
public:
	void SetBool(
		ShaderTypes shader_type, 
		const GString& val_name, 
		BOOL b);
	void SetBoolArray(
		ShaderTypes shader_type,
		const GString& val_name,
		const BOOL* pB,
		UINT Count
		);
	void SetFloat(
		ShaderTypes shader_type,
		const GString& val_name,
		float f
		);
	void SetFloatArray(
		ShaderTypes shader_type, 
		const GString& val_name,
		const float* pF,
		UINT Count
		);
	void SetInt(
		ShaderTypes shader_type,
		const GString& val_name,
		int i
		);
	void SetIntArray(
		ShaderTypes shader_type,
		const GString& val_name,
		const int* pI,
		UINT Count
		);
	void SetMatrix(
		ShaderTypes shader_type,
		const GString& val_name,
		const D3DXMATRIX* pMatrix
		);
	void SetMatrixArray(
		ShaderTypes shader_type, 
		const GString& val_name, 
		const D3DXMATRIX* pMatrix,
		UINT Count
		);
	void SetMatrixPointerArray(
		ShaderTypes shader_type, 
		const GString& val_name, 
		const D3DXMATRIX** pMatrix,
		UINT Count
		);
	void SetMatrixTranspose(
		ShaderTypes shader_type, 
		const GString& val_name,
		const D3DXMATRIX* pMatrix
		);
	void SetMatrixTransposeArray(
		ShaderTypes shader_type, 
		const GString& val_name, 
		const D3DXMATRIX* pMatrix,
		UINT Count
		);
	void SetMatrixTransposePointerArray(
		ShaderTypes shader_type, 
		const GString& val_name,
		const D3DXMATRIX** pMatrix,
		UINT Count
		);
	void SetValue(
		ShaderTypes shader_type, 
		const GString& val_name, 
		void* pData,
		UINT Bytes
		);
	void SetVector(
		ShaderTypes shader_type,
		const GString& val_name,
		const D3DXVECTOR4* pVector
		);
	void SetVectorArray(
		ShaderTypes shader_type, 
		const GString& val_name,
		const D3DXVECTOR4* pVector,
		UINT Count
		);

};
#endif