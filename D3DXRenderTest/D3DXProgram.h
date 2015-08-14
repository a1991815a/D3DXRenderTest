#ifndef __D3DXPROGRAM__
#define __D3DXPROGRAM__
#include "D3DXHeader.h"
#include <string>
#include <unordered_map>

enum ShaderVersion{
	VS_2_0,
	PS_2_0
};

class D3DXProgram{
private:
	IDirect3DVertexShader9* m_vShader;
	IDirect3DPixelShader9* m_fShader;
	ID3DXConstantTable* m_vTable;
	ID3DXConstantTable* m_fTable;
	std::unordered_map<std::string, D3DXHANDLE> m_vDataHandle;
	std::unordered_map<std::string, D3DXHANDLE> m_fDataHandle;
public:
	D3DXProgram();
	~D3DXProgram();
	void setVShader(IDirect3DVertexShader9* vShader);
	void setPShader(IDirect3DPixelShader9* fShader);
	
	IDirect3DVertexShader9* getVShader();
	IDirect3DPixelShader9* getFShader();
	ID3DXConstantTable* getVTable();
	ID3DXConstantTable* getFTable();

	void initVTable(const std::string& val_name);
	void initFTable(const std::string& val_name);
	D3DXHANDLE getHandle(const std::string& key);

	static void init(IDirect3DDevice9* device);

	static void createShaderFromFile(
		const std::string& file_name,
		ShaderVersion version, 
		D3DXProgram* program);

	static void createShaderFromData(
		const std::string& source,
		ShaderVersion version, 
		D3DXProgram* program);

	static const char* getVersion(ShaderVersion version);
};
#endif