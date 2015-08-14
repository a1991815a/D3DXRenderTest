#include "D3DXProgram.h"
#include "MacroHeader.h"
#include "GBAssert.h"
#include "AppdeleGate.h"

static IDirect3DDevice9* d3dx_device = nullptr;

void D3DXProgram::init(IDirect3DDevice9* device)
{
	d3dx_device = device;
}

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

void D3DXProgram::setPShader(IDirect3DPixelShader9* fShader)
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

ID3DXConstantTable* D3DXProgram::getVTable()
{
	return m_vTable;
}

ID3DXConstantTable* D3DXProgram::getFTable()
{
	return m_fTable;
}

void D3DXProgram::initVTable(const std::string& key, const std::string& val)
{
	D3DXHANDLE handle = m_vTable->GetConstantByName(0, val.c_str());
	m_DataHandle[key] = handle;
}

void D3DXProgram::initFTable(const std::string& key, const std::string& val)
{
	D3DXHANDLE handle = m_fTable->GetConstantByName(0, val.c_str());
	m_DataHandle[key] = handle;
}

D3DXHANDLE D3DXProgram::getHandle(const std::string& key)
{
	return m_DataHandle.at(key);
}

void D3DXProgram::createShaderFromFile(
	const std::string& file_name,
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
			"vmain",
			getVersion(version),
			D3DXSHADER_DEBUG,
			&buf,
			&error_buf,
			&program->m_vTable
			);

		if (result != D3D_OK)
		{
			char debug_text[1024] = { 0 };
			sprintf_s(debug_text, "%s \n", (char*)error_buf->GetBufferPointer());
			OutputDebugStringA(debug_text);
		}

		GBASSERT(result == D3D_OK);
		_renderEngine->getDevice()->CreateVertexShader((DWORD*)buf->GetBufferPointer(), &program->m_vShader);
		SAFE_RELEASE_COM(buf);
	}
	else if(version == PS_2_0) {
		HRESULT result = D3D_OK;
		ID3DXBuffer* buf = nullptr;
		ID3DXBuffer* error_buf = nullptr;
		result = D3DXCompileShaderFromFileA(
			file_name.c_str(),
			nullptr,
			nullptr,
			"fmain",
			getVersion(version),
			D3DXSHADER_DEBUG,
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
		_renderEngine->getDevice()->CreatePixelShader((DWORD*)buf->GetBufferPointer(), &program->m_fShader);
		SAFE_RELEASE_COM(buf);
	}
}

void D3DXProgram::createShaderFromData(
	const std::string& source, 
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
			D3DXSHADER_DEBUG,
			&buf,
			&error_buf,
			&program->m_vTable
			);
		GBASSERT(result == D3D_OK);
		_renderEngine->getDevice()->CreateVertexShader((DWORD*)buf->GetBufferPointer(), &program->m_vShader);
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
			D3DXSHADER_DEBUG,
			&buf,
			&error_buf,
			&program->m_fTable
			);
		GBASSERT(result == D3D_OK);
		_renderEngine->getDevice()->CreatePixelShader((DWORD*)buf->GetBufferPointer(), &program->m_fShader);
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

