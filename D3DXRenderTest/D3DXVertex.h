#ifndef __D3DXVERTEX__
#define __D3DXVERTEX__
#include "Vec.h"

class Vertex{
public:
	Vec3 position;
	Color4f color;
	Vec3 normal;
	Vec2 texcoord;
private:
	static DWORD							m_fvf;
	static IDirect3DVertexDeclaration9*		m_decl;

public:
	Vertex()
		:position(), color(), normal()
	{};
	Vertex(real x, real y, real z)
		:position(x, y, z) 
	{};
	Vertex(const Vec3& pos)
		:position(pos)
	{};
	Vertex(const Vec3& pos, const Color4f& color)
		:position(pos), color(color)
	{};
	Vertex(const Vec3& pos, const Color4f& color, const Vec3& normal)
		:position(pos), color(color), normal(normal)
	{};

	virtual ~Vertex(){};

	virtual DWORD getFVF() const
	{
		return Vertex::m_fvf;
	};
	virtual IDirect3DVertexDeclaration9* getVertexDecl() const {
		return Vertex::m_decl;
	};
	virtual size_t getSize() const {
		return sizeof(Vertex);
	};

	static void init();
	static void destroy();

	Vertex* getNextVertex(size_t i) {
		char* p = (char*)this;
		p += this->getSize() * i;
		return (Vertex*)p;
	};


};

class Vertex_Point : public Vertex{
	friend class Vertex;
private:
	static DWORD							m_fvf;
	static IDirect3DVertexDeclaration9*		m_decl;
public:
	float psize;
public:
	Vertex_Point()
		:Vertex(), psize(1)
	{};
	Vertex_Point(real x, real y, real z)
		:Vertex(x, y, z), psize(1)
	{};
	Vertex_Point(const Vec3& pos)
		:Vertex(pos), psize(1)
	{};
	Vertex_Point(const Vec3& pos, const Color4f& color)
		:Vertex(pos, color), psize(1)
	{};
	Vertex_Point(const Vec3& pos, const Color4f& color, const Vec3& normal)
		:Vertex(pos, color, normal), psize(1)
	{};
	Vertex_Point(const Vec3& pos, const Color4f& color, const Vec3& normal, float psize)
		:Vertex(pos, color, normal), psize(psize)
	{};

	virtual DWORD getFVF() const override
	{
		return Vertex_Point::m_fvf;
	};
	virtual IDirect3DVertexDeclaration9* getVertexDecl() const override {
		return Vertex_Point::m_decl;
	};
	virtual size_t getSize() const override {
		return sizeof(Vertex_Point);
	};
};


#endif