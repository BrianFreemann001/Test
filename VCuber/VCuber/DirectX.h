#pragma once
#include "stdafx.h"

class Dx
{

	ID3D11Texture2D *depthStencilBuffer = nullptr;
	ID3D11DepthStencilState *depthStencilState = nullptr;
	ID3D11RasterizerState *rasterState = nullptr;
	D3D11_VIEWPORT *viewport = nullptr;
	ID3D11Texture2D *backBuffer = nullptr;
	DXGI_SWAP_CHAIN_DESC swapchaindesc;
	float dwidth = 1280.0f, dheight = 720.0f;

	void CreateDeviceAndSwapchain(float width, float height, bool is_vsync, bool is_fullscreen);
	void CreateDepthStencilandRasterState();
	void CreateViewport(float width, float height);
	void InitPipelineStages();
public:
	ID3D11Device * device = nullptr;
	IDXGISwapChain *swapchain = nullptr;
	ID3D11DeviceContext *deviceContext = nullptr;
	ID3D11RenderTargetView *render_target = nullptr;
	ID3D11DepthStencilView *depthStencilView = nullptr;
	void StartUp(float width, float height, bool is_vsync, bool is_fullscreen);
	void ShutDown();
};