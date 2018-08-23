#pragma once
#include "stdafx.h"
#include "PhysicsObj.h"
#include "Mesh.h"

class Physics
{
public:
	bool RayCollisionWithAABB(AABB _box, Ray &_ray, Vertex& _intersection, Vertex &fraction);
	bool AABBCollisionWithAABB(AABB _box1, AABB _box2);
	bool ClipAxis(int _axis, AABB _box, Vertex _v0, Vertex _v1, float& _low, float& _high);

};

struct DebugRenderer
{
	struct DebugLine
	{
		Vertex a, b;
	};
private:
	std::vector<DebugLine> lines;
public:
	void AddLine(Vertex _a, Vertex _b);
	void SendToBuffer(Vertex *tempverts);
};