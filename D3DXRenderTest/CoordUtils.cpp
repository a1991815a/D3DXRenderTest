#include "CoordUtils.h"
#include <assert.h>

Vec2 WorldToNode(const Node* node, const Vec2& point)
{
	Vec2 ret = point;

	D3DXMATRIX matrix;
	D3DXMatrixInverse(&matrix, nullptr, node->getTransformMatrix());

	D3DXVec2TransformCoord(
		ret.getD3DXVector(),
		ret.getD3DXVector(),
		&matrix);

	return ret;
}

Vec2 NodeToWorld(const Node* node, const Vec2& point)
{
	Vec2 ret = point;
	D3DXVec2TransformCoord(
		ret.getD3DXVector(),
		ret.getD3DXVector(),
		node->getTransformMatrix()
		);

	return ret;
}
