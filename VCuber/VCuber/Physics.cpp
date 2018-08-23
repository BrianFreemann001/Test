#include "stdafx.h"
#include "Physics.h"

bool Physics::RayCollisionWithAABB(AABB _box, Ray &_ray, Vertex& _intersection, Vertex &fraction)
{
	Vertex low;
	low.position.x = 0;
	low.position.y = 0;
	low.position.z = 0;
	Vertex high;
	high.position.x = 1;
	high.position.y = 1;
	high.position.z = 1;

	if (!ClipAxis(0, _box, _ray.src, _ray.dest, low.position.x, high.position.x))
		return false;
	if (!ClipAxis(1, _box, _ray.src, _ray.dest, low.position.y, high.position.y))
		return false;
	if (!ClipAxis(2, _box, _ray.src, _ray.dest, low.position.z, high.position.z))
		return false;

	Vertex difference = _ray.dest - _ray.src;
	_intersection = _ray.src + difference * low;

	fraction = low;

	return true;
}

bool Physics::AABBCollisionWithAABB(AABB a, AABB b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return false;
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return false;

	return true;
}

bool Physics::ClipAxis(int _axis, AABB _box, Vertex _v0, Vertex _v1, float & _low, float & _high)
{
	float axisLow, axisHigh;

	if (_axis == 0)
	{
		axisLow = (_box.min.x - _v0.position.x) / (_v1.position.x - _v0.position.x);
		axisHigh = (_box.max.x - _v0.position.x) / (_v1.position.x - _v0.position.x);
	}
	else if (_axis == 1)
	{
		axisLow = (_box.min.y - _v0.position.y) / (_v1.position.y - _v0.position.y);
		axisHigh = (_box.max.y - _v0.position.y) / (_v1.position.y - _v0.position.y);
	}
	else if (_axis == 2)
	{
		axisLow = (_box.min.z - _v0.position.z) / (_v1.position.z - _v0.position.z);
		axisHigh = (_box.max.z - _v0.position.z) / (_v1.position.z - _v0.position.z);
	}

	if (axisHigh < axisLow)
		std::swap(axisHigh, axisLow);

	if (axisHigh < _low)
		return false;

	if (axisLow > _high)
		return false;

	_low = max(axisLow, _low);
	_high = min(axisHigh, _high);

	if (_low > _high)
		return false;

	return true;
}

void DebugRenderer::AddLine(Vertex _a, Vertex _b)
{
	DebugLine tempLine;
	tempLine.a = _a;
	tempLine.b = _b;
	lines.push_back(tempLine);
}

void DebugRenderer::SendToBuffer(Vertex *tempverts)
{

	for (int i = 0; i < lines.size(); i++)
	{
		tempverts[i * 2].position = lines[i].a.position;
		tempverts[i * 2].normals = lines[i].a.normals;
		tempverts[i * 2].uv = lines[i].a.uv;

		tempverts[(i * 2) + 1].position = lines[i].b.position;
		tempverts[(i * 2) + 1].normals = lines[i].b.normals;
		tempverts[(i * 2) + 1].uv = lines[i].b.uv;
	}
}
