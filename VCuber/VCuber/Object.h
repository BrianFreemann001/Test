#pragma once
#include "stdafx.h"
#include "AI.h"
#include "Animation.h"
#include "Mesh.h"
#include "PhysicsObj.h"
#include "Shader.h"

class Object
{
	std::string name;
	DirectX::XMMATRIX localTransform;
	DirectX::XMMATRIX worldTransform;
public:
	Shader *objShaders = nullptr;
	Mesh objMesh;
//	AABB collider;
	ID3D11Buffer *vertexBuffer;
	Animation *objAnimation = nullptr;
	ID3D11Texture2D  *diffuseTexture = nullptr;
	ID3D11ShaderResourceView *diffuseTextureSRV = nullptr;
	Object()
	{
		objShaders = new Shader;
		objAnimation = new Animation;
		localTransform = DirectX::XMMatrixIdentity();
		worldTransform = DirectX::XMMatrixIdentity();
	}
	~Object()
	{
		delete objShaders;
		delete objAnimation;
	}

	//Accessors
	std::string GetName()
	{
		return name;
	}
	DirectX::XMMATRIX GetTransform()
	{
		return localTransform;
	}
	DirectX::XMMATRIX GetWorldTransform()
	{
		return worldTransform;
	}
	//Mutators
	void SetName(std::string _name)
	{
		name = _name;
	}
	void SetTransform(DirectX::XMMATRIX _matrix)
	{
		localTransform = _matrix;
	}
	void SetWorldTransform(DirectX::XMMATRIX _matrix)
	{
		worldTransform = _matrix;
	}
};