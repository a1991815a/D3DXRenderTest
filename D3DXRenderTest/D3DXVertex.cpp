#include "D3DXVertex.h"
#include "MacroHeader.h"

static IDirect3DDevice9* d3dx_device = nullptr;

DWORD Vertex_pos::m_FVF = D3DFVF_XYZ;
DWORD Vertex_pos_normal::m_FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
DWORD Vertex_pos_color::m_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
DWORD Vertex_pos_color_normal::m_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL;

IDirect3DVertexDeclaration9* Vertex_pos::m_decl = nullptr;
IDirect3DVertexDeclaration9* Vertex_pos_normal::m_decl = nullptr;
IDirect3DVertexDeclaration9* Vertex_pos_color::m_decl = nullptr;
IDirect3DVertexDeclaration9* Vertex_pos_color_normal::m_decl = nullptr;

void Vertex::init(IDirect3DDevice9* device)
{
	d3dx_device = device;
	{
		D3DVERTEXELEMENT9 ele[] = { 
			{0, sizeof(Vertex), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, },
			D3DDECL_END()
		};

		d3dx_device->CreateVertexDeclaration(&ele[0], &Vertex_pos::m_decl);
	}

	{
		D3DVERTEXELEMENT9 ele[] = { 
			{0, sizeof(Vertex), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0, },
			{0, sizeof(Vertex) + sizeof(Vertex_pos), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, },
			D3DDECL_END()
		};

		d3dx_device->CreateVertexDeclaration(&ele[0], &Vertex_pos_normal::m_decl);
	}

	{
		D3DVERTEXELEMENT9 ele[] = { 
			{0, sizeof(Vertex), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0, },
			{0, sizeof(Vertex) + sizeof(Vertex_pos), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0, },
			D3DDECL_END()
		};

		d3dx_device->CreateVertexDeclaration(&ele[0], &Vertex_pos_color::m_decl);
	}

	{
		D3DVERTEXELEMENT9 ele[] = { 
			{0, sizeof(Vertex), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0, },
			{0, sizeof(Vertex) + sizeof(Vertex_pos), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0, },
			{0, sizeof(Vertex) + sizeof(Vertex_pos_color), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, },
			D3DDECL_END()
		};

		d3dx_device->CreateVertexDeclaration(&ele[0], &Vertex_pos_color_normal::m_decl);
	}
}

void Vertex::destroy()
{
	SAFE_RELEASE_COM(Vertex_pos::m_decl);
	SAFE_RELEASE_COM(Vertex_pos_color::m_decl);
	SAFE_RELEASE_COM(Vertex_pos_normal::m_decl);
	SAFE_RELEASE_COM(Vertex_pos_color_normal::m_decl);
}

Vertex_pos::Vertex_pos()
	:position(0, 0, 0)
{

}

Vertex_pos::Vertex_pos(real x, real y, real z)
	:position(x, y, z)
{

}

DWORD Vertex_pos::getFVF() const
{
	return D3DFVF_XYZ;
}

IDirect3DVertexDeclaration9* Vertex_pos::getVertexDecl() const 
{
	return Vertex_pos::m_decl;
}

size_t Vertex_pos::getSize() const 
{
	return sizeof(Vertex_pos);
}

DWORD Vertex_pos_normal::getFVF() const 
{
	return D3DFVF_XYZ | D3DFVF_NORMAL;
}

IDirect3DVertexDeclaration9* Vertex_pos_normal::getVertexDecl() const 
{
	return Vertex_pos_normal::m_decl;
}

size_t Vertex_pos_normal::getSize() const 
{
	return sizeof(Vertex_pos_normal);
}

DWORD Vertex_pos_color::getFVF() const 
{
	return D3DFVF_XYZ | D3DFVF_DIFFUSE;
}

IDirect3DVertexDeclaration9* Vertex_pos_color::getVertexDecl() const 
{
	return Vertex_pos_color::m_decl;
}

size_t Vertex_pos_color::getSize() const 
{
	return sizeof(Vertex_pos_color);
}

DWORD Vertex_pos_color_normal::getFVF() const 
{
	return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL;
}

IDirect3DVertexDeclaration9* Vertex_pos_color_normal::getVertexDecl() const 
{
	return Vertex_pos_color_normal::m_decl;
}

size_t Vertex_pos_color_normal::getSize() const 
{
	return sizeof(Vertex_pos_color_normal);
}
