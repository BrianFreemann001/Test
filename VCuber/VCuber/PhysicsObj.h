#pragma once
#include "stdafx.h"
#include "Object.h"

struct AABB
{
	DirectX::XMFLOAT3 min, max;
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
};
struct Ray
{
	Vertex src, dest;
	DirectX::XMMATRIX worldMatrix;
};

class PhysicsObj
{
public:
	AABB testCollider;
	Ray testRay;
};

