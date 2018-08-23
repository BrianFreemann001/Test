#pragma once
#include "stdafx.h"
class ShaderLoader
{
	Dx *directX = nullptr;
public:
	ShaderLoader(Dx *_directX)
	{
		directX = _directX;
	}
	void CreatePixelShader(const void *shaderByteCode, ID3D11PixelShader **pixelShader);
	void CreateVertexShader(const void *shaderByteCode, ID3D11VertexShader **vertexShader);
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *inputElementDesc, const void *shaderByteCode, ID3D11InputLayout **inputLayout);
	~ShaderLoader()
	{
		delete directX;
	}
};