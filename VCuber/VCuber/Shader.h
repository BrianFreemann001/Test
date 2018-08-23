#pragma once
#include "stdafx.h"

class Shader
{

public:
	ID3D11InputLayout *inputLayout = nullptr;
	ID3D11VertexShader *vertexShader = nullptr;
	ID3D11PixelShader * pixelShader = nullptr;
};