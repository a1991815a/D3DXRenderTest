#include "D3DXProgram.h"
#include "MacroHeader.h"
#include "GBAssert.h"
#include "D3DXGlobalFunction.h"

#define SHADER_FLAG D3DXSHADER_DEBUG | D3DXSHADER_USE_LEGACY_D3DX9_31_DLL

D3DXProgram::D3DXProgram()
	:m_vShader(nullptr), m_fShader(nullptr),
	m_vTable(nullptr), m_fTable(nullptr)
{ 

}

D3DXProgram::~D3DXProgram()
{
	SAFE_RELEASE_COM(m_vTable);
	SAFE_RELEASE_COM(m_fTable);
	SAFE_RELEASE_COM(m_vShader);
	SAFE_RELEASE_COM(m_fShader);
}

void D3DXProgram::setVShader(IDirect3DVertexShader9* vShader)
{
	m_vShader = vShader;
}

void D3DXProgram::setFShader(IDirect3DPixelShader9* fShader)
{
	m_fShader = fShader;
}

IDirect3DVertexShader9* D3DXProgram::getVShader()
{
	return m_vShader;
}

IDirect3DPixelShader9* D3DXProgram::getFShader()
{
	return m_fShader;
}

ID3DXConstantTable* D3DXProgram::getTable(ShaderTypes shader_type)
{
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		return m_vTable;
	case D3D_PIXEL_SHADER:
		return m_fTable;
	}
	return nullptr;
}

void D3DXProgram::initVTable(const GString& val_name)
{
	D3DXHANDLE handle = m_vTable->GetConstantByName(0, val_name.c_str());
	m_vDataHandle[val_name] = handle;
}

void D3DXProgram::initFTable(const GString& val_name)
{
	D3DXHANDLE handle = m_fTable->GetConstantByName(0, val_name.c_str());
	m_fDataHandle[val_name] = handle;
}

D3DXHANDLE D3DXProgram::getHandle(const GString& key, ShaderTypes shader_type)
{
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		return m_vDataHandle.at(key);
	case D3D_PIXEL_SHADER:
		return m_fDataHandle.at(key);
	default:
		break;
	}
	return nullptr;
}

void D3DXProgram::createShaderFromFile(
	const GString& file_name,
	ShaderVersion version, 
	D3DXProgram* program)
{
	if (version == VS_2_0) {
		HRESULT result = D3D_OK;
		ID3DXBuffer* buf = nullptr;
		ID3DXBuffer* error_buf = nullptr;
		result = D3DXCompileShaderFromFileA(
			file_name.c_str(),
			nullptr,
			nullptr,
			"main",
			getVersion(version),
			SHADER_FLAG,
			&buf,
			&error_buf,
			&program->m_vTable
			);

		if (result != D3D_OK && error_buf)
		{
			char debug_text[1024] = { 0 };
			sprintf_s(debug_text, "%s \n", (char*)error_buf->GetBufferPointer());
			OutputDebugStringA(debug_text);
		}

		GBASSERT(result == D3D_OK);
		dxGetDevice()->CreateVertexShader((DWORD*)buf->GetBufferPointer(), &program->m_vShader);
		SAFE_RELEASE_COM(buf);
		program->m_vTable->SetDefaults(dxGetDevice());
	}
	else if(version == PS_2_0) {
		HRESULT result = D3D_OK;
		ID3DXBuffer* buf = nullptr;
		ID3DXBuffer* error_buf = nullptr;
		result = D3DXCompileShaderFromFileA(
			file_name.c_str(),
			nullptr,
			nullptr,
			"main",
			getVersion(version),
			SHADER_FLAG,
			&buf,
			&error_buf,
			&program->m_fTable
			);

		if (result != D3D_OK)
		{
			char debug_text[1024] = { 0 };
			sprintf_s(debug_text, "%s \n", (char*)error_buf->GetBufferPointer());
			OutputDebugStringA(debug_text);
		}

		GBASSERT(result == D3D_OK);
		dxGetDevice()->CreatePixelShader((DWORD*)buf->GetBufferPointer(), &program->m_fShader);
		SAFE_RELEASE_COM(buf);
		program->m_fTable->SetDefaults(dxGetDevice());
	}
}

void D3DXProgram::createShaderFromData(
	const GString& source, 
	ShaderVersion version, 
	D3DXProgram* program)
{
	if (version == VS_2_0) {
		HRESULT result = D3D_OK;
		ID3DXBuffer* buf = nullptr;
		ID3DXBuffer* error_buf = nullptr;
		result = D3DXCompileShader(
			source.c_str(),
			source.size(),
			nullptr,
			nullptr,
			"vmain",
			getVersion(version),
			SHADER_FLAG,
			&buf,
			&error_buf,
			&program->m_vTable
			);
		GBASSERT(result == D3D_OK);
		dxGetDevice()->CreateVertexShader((DWORD*)buf->GetBufferPointer(), &program->m_vShader);
		SAFE_RELEASE_COM(buf);
	}
	else if (version == PS_2_0) {
		HRESULT result = D3D_OK;
		ID3DXBuffer* buf = nullptr;
		ID3DXBuffer* error_buf = nullptr;
		result = D3DXCompileShader(
			source.c_str(),
			source.size(),
			nullptr,
			nullptr,
			"fmain",
			getVersion(version),
			SHADER_FLAG,
			&buf,
			&error_buf,
			&program->m_fTable
			);
		GBASSERT(result == D3D_OK);
		dxGetDevice()->CreatePixelShader((DWORD*)buf->GetBufferPointer(), &program->m_fShader);
		SAFE_RELEASE_COM(buf);
	}
}

const char* D3DXProgram::getVersion(ShaderVersion version)
{
	switch(version){
	case VS_2_0:
		return "vs_2_0";
	case PS_2_0:
		return "ps_2_0";
	default:
		break;
	}
	return nullptr;
}

void D3DXProgram::SetBool(ShaderTypes shader_type, const GString& val_name, BOOL b)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetBool(dxGetDevice(), handle, b);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetBool(dxGetDevice(), handle, b);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetBoolArray(ShaderTypes shader_type, const GString& val_name, const BOOL* pB, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetBoolArray(dxGetDevice(), handle, pB, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetBoolArray(dxGetDevice(), handle, pB, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetFloat(ShaderTypes shader_type, const GString& val_name, float f)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetFloat(dxGetDevice(), handle, f);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetFloat(dxGetDevice(), handle, f);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetFloatArray(ShaderTypes shader_type, const GString& val_name, const float* pF, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetFloatArray(dxGetDevice(), handle, pF, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetFloatArray(dxGetDevice(), handle, pF, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetInt(ShaderTypes shader_type, const GString& val_name, int i)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetInt(dxGetDevice(), handle, i);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetInt(dxGetDevice(), handle, i);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetIntArray(ShaderTypes shader_type, const GString& val_name, const int* pI, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetIntArray(dxGetDevice(), handle, pI, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetIntArray(dxGetDevice(), handle, pI, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrix(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX* pMatrix)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrix(dxGetDevice(), handle, pMatrix);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrix(dxGetDevice(), handle, pMatrix);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrixArray(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX* pMatrix, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrixArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrixArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrixPointerArray(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX** pMatrix, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrixPointerArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrixPointerArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrixTranspose(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX* pMatrix)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrixTranspose(dxGetDevice(), handle, pMatrix);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrixTranspose(dxGetDevice(), handle, pMatrix);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrixTransposeArray(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX* pMatrix, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrixTransposeArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrixTransposeArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetMatrixTransposePointerArray(ShaderTypes shader_type, const GString& val_name, const D3DXMATRIX** pMatrix, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetMatrixTransposePointerArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetMatrixTransposePointerArray(dxGetDevice(), handle, pMatrix, Count);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetValue(ShaderTypes shader_type, const GString& val_name, void* pData, UINT Bytes)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetValue(dxGetDevice(), handle, pData, Bytes);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetValue(dxGetDevice(), handle, pData, Bytes);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetVector(ShaderTypes shader_type, const GString& val_name, const D3DXVECTOR4* pVector)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetVector(dxGetDevice(), handle, pVector);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetVector(dxGetDevice(), handle, pVector);
		return;
	}
	GBASSERT(false);
}

void D3DXProgram::SetVectorArray(ShaderTypes shader_type, const GString& val_name, const D3DXVECTOR4* pVector, UINT Count)
{
	D3DXHANDLE handle = getHandle(val_name, shader_type);
	switch (shader_type)
	{
	case D3D_VERTEX_SHADER:
		m_vTable->SetVectorArray(dxGetDevice(), handle, pVector, Count);
		return;
	case D3D_PIXEL_SHADER:
		m_fTable->SetVectorArray(dxGetDevice(), handle, pVector, Count);
		return;
	}
	GBASSERT(false);
}

