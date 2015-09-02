#include "CoordUtils.h"
#include <assert.h>
#include "Director.h"

Vec2 WorldToNode(const Node* node, const Vec2& point)
{
	Vec2 ret = point;

	D3DXMATRIX matrix;
	D3DXMatrixInverse(&matrix, nullptr, node->getTransformMatrix());

	D3DXVec2TransformCoord(
		ret.getD3DXVector(),
		ret.getD3DXVector(),
		&matrix
		);
	ret.x += node->getPosition().x / _director->getWindowSize().x * 15;
	ret.y += node->getPosition().y / _director->getWindowSize().y * 30;
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
