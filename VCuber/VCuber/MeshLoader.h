#pragma once
#include "Mesh.h"

struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

struct VertexPositionUVNormal
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 uv;
	DirectX::XMFLOAT3 normal;
};

class MeshLoader
{

public:
	std::vector<std::string> GetMeshList(const char* filename);
	Mesh ReadMesh(const char* filepath);
	void ReadMaterial(char* filepath);
};