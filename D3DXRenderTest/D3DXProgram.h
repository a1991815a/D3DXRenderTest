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
	void setVShader(IDirect3DVertexShader9* vShader);	//设置顶点着色器
	void setFShader(IDirect3DPixelShader9* fShader);	//设置片段着色器
	
	IDirect3DVertexShader9* getVShader();				//得到顶点着色器
	IDirect3DPixelShader9* getFShader();				//得到片段着色器
	ID3DXConstantTable* getTable(ShaderTypes shader_type);					//得到常量表

	void initVTable(const GString& val_name);		//初始化顶点常量表
	void initFTable(const GString& val_name);		//初始化片段常量表
	D3DXHANDLE getHandle(
		const GString& key, 
		ShaderTypes shader_type);						//得到变量句柄



	//从文件创建Shader
	static void createShaderFromFile(
		const GString& file_name,
		ShaderVersion version, 
		D3DXProgram* program);
	//从数据创建Shader
	static void createShaderFromData(
		const GString& source,
		ShaderVersion version, 
		D3DXProgram* program);
	//得到版本字符串
	static const char* getVersion(ShaderVersion version);


/*
	向常量表输入数据
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