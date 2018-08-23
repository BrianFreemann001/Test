#include "stdafx.h"
#include "ShaderLoader.h"

void ShaderLoader::CreatePixelShader(const void *shaderByteCode, ID3D11PixelShader **pixelShader)
{

	directX->device->CreatePixelShader(shaderByteCode, sizeof(shaderByteCode), NULL, pixelShader);
}

void ShaderLoader::CreateVertexShader(const void *shaderByteCode, ID3D11VertexShader **vertexShader)
{
	directX->device->CreateVertexShader(shaderByteCode, sizeof(shaderByteCode), NULL, vertexShader);
}

void ShaderLoader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *inputElementDesc, const void *shaderByteCode, ID3D11InputLayout **inputLayout)
{

	directX->device->CreateInputLayout(inputElementDesc, 2, shaderByteCode, sizeof(shaderByteCode), inputLayout);
}