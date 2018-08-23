#pragma once
#include "stdafx.h"


struct Vertex
{

	DirectX::XMFLOAT3 position;	//xyz
	DirectX::XMFLOAT3 normals;	//rgb
	DirectX::XMFLOAT2 uv;		//texture coordiates

	Vertex() {

	}

	Vertex(float x, float y, float z, float r, float g, float b, float u, float v)
	{

		position.x = x;
		position.y = y;
		position.z = z;
		normals.x = r;
		normals.y = g;
		normals.z = b;
		uv.x = u;
		uv.y = v;
	}

	Vertex operator+(Vertex b);
	Vertex operator-(Vertex b);
	Vertex operator*(Vertex b);
	Vertex operator/(Vertex b);
};

struct alignas(16) float4 : std::array<float, 4> { using std::array<float, 4>::array;  };
struct BasicMaterial
{

	float4 value;
	const char* filepath;

	BasicMaterial()
	{
		filepath = nullptr;
	}
};

class Mesh
{
	public:
	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;
};