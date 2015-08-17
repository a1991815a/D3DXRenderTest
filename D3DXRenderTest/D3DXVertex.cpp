#include "D3DXVertex.h"
#include "MacroHeader.h"
#include "D3DXGlobalFunction.h"

DWORD Vertex::m_fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL;
DWORD Vertex_Point::m_fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_PSIZE;


IDirect3DVertexDeclaration9* Vertex::m_decl = nullptr;
IDirect3DVertexDeclaration9* Vertex_Point::m_decl = nullptr;


void Vertex::init()
{
	{
		D3DVERTEXELEMENT9 ele[] = {
			{ 0, 4, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, },
			{ 0, 4 + sizeof(Vec3), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0, },
			{ 0, 4 + sizeof(Vec3) + sizeof(Color4f), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, },
			D3DDECL_END()
		};
		dxGetDevice()->CreateVertexDeclaration(&ele[0], &Vertex::m_decl);
	}

	{
		D3DVERTEXELEMENT9 ele[] = {
			{ 0, 4, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0, },
			{ 0, 4 + sizeof(Vec3), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0, },
			{ 0, 4 + sizeof(Vec3) + sizeof(Color4f), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0, },
			{ 0, 4 + sizeof(Vec3) + sizeof(Color4f) + sizeof(Vec3), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0, },
			D3DDECL_END()
		};
		dxGetDevice()->CreateVertexDeclaration(&ele[0], &Vertex_Point::m_decl);
	}
	
}

void Vertex::destroy()
{
	SAFE_RELEASE_COM(Vertex::m_decl);
}