#ifndef __COORDUTILS__
#define __COORDUTILS__
#include "Vec.h"
#include "Node.h"

Vec2 WorldToNode(const Node* node, const Vec2& point);

Vec2 NodeToWorld(const Node* node, const Vec2& point);
#endif