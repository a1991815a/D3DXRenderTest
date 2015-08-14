#ifndef __D3DXVERTEX__
#define __D3DXVERTEX__
#include "Vec.h"

class Vertex{
public:
	virtual ~Vertex(){};
	virtual DWORD getFVF() const = 0;
	virtual IDirect3DVertexDeclaration9* getVertexDecl() const = 0;
	virtual size_t getSize() const = 0;
	static void init(IDirect3DDevice9* device);
	static void destroy();
};

class Vertex_pos: public Vertex{
	friend class Vertex;
public:
	Vertex_pos();
	Vertex_pos(real x, real y, real z);

	Vec3 position;

	virtual DWORD getFVF() const override;

	virtual IDirect3DVertexDeclaration9* getVertexDecl() const override;

	virtual size_t getSize() const override;
private:
	static DWORD m_FVF;
	static IDirect3DVertexDeclaration9* m_decl;
};

class Vertex_pos_normal: public Vertex_pos{
	friend class Vertex;
public:
	Vec3 normal;

	virtual DWORD getFVF() const override;

	virtual IDirect3DVertexDeclaration9* getVertexDecl() const override;

	virtual size_t getSize() const override;
private:
	static DWORD m_FVF;
	static IDirect3DVertexDeclaration9* m_decl;
};

class Vertex_pos_color: public Vertex_pos{
	friend class Vertex;
public:
	Color4f color;

	virtual DWORD getFVF() const override;

	virtual IDirect3DVertexDeclaration9* getVertexDecl() const override;

	virtual size_t getSize() const override;
private:
	static DWORD m_FVF;
	static IDirect3DVertexDeclaration9* m_decl;
};

class Vertex_pos_color_normal: public Vertex_pos_color{
	friend class Vertex;
public:
	Vec3 normal;

	virtual DWORD getFVF() const override;

	virtual IDirect3DVertexDeclaration9* getVertexDecl() const override;

	virtual size_t getSize() const override;
private:
	static DWORD m_FVF;
	static IDirect3DVertexDeclaration9* m_decl;
};

#endif