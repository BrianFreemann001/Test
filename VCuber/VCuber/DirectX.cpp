#include "stdafx.h"
#include "DirectX.h"


//Private Helper Functions
void Dx::CreateDeviceAndSwapchain(float width, float height, bool is_vsync, bool is_fullscreen)
{

	//Resize window to match fullscreen, else continue with inittial input;
	if (is_fullscreen)
	{

		RECT desktop;
		GetWindowRect(GetDesktopWindow(), &desktop);
		width = (float)desktop.right;
		height = (float)desktop.bottom;
	}
	dwidth = width;
	dheight = height;
	// Set VSYNC options else carryon

	//Create SwapChain Descriptor
	ZeroMemory(&swapchaindesc, sizeof(swapchaindesc));
	swapchaindesc.BufferCount = 1;
	swapchaindesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchaindesc.BufferDesc.Height = (UINT) height;
	swapchaindesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchaindesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchaindesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swapchaindesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchaindesc.BufferDesc.Width = (UINT) width;
	swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchaindesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapchaindesc.OutputWindow = GetActiveWindow();
	swapchaindesc.SampleDesc.Count = 1;
	swapchaindesc.SampleDesc.Quality = 0;
	swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchaindesc.Windowed = true;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swapchaindesc, &swapchain, &device, NULL, &deviceContext);
}

void Dx::InitPipelineStages()
{

	//deviceContext->VSSetShader(vertex_shader, NULL, 0);
	//deviceContext->IASetInputLayout(input_layout);
	//deviceContext->PSSetShader(pixel_shader, NULL, 0);
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	device->CreateRenderTargetView(backBuffer, NULL, &render_target);
	deviceContext->ClearRenderTargetView(render_target, DirectX::Colors::Crimson);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	deviceContext->OMSetRenderTargets(1, &render_target, depthStencilView);
}

void Dx::CreateDepthStencilandRasterState()
{

	deviceContext->RSSetState(rasterState);

	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		(UINT) dwidth,
		(UINT) dheight,
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
	);

	device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);

	device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer);
}

void Dx::CreateViewport(float width, float height)
{
	viewport = new D3D11_VIEWPORT();
	viewport->Height = height;
	viewport->Width = width;
	viewport->TopLeftX = 0;
	viewport->TopLeftY = 0;
	viewport->MinDepth = 0;
	viewport->MaxDepth = 1.0f;
	deviceContext->RSSetViewports(1, viewport);
}

//Public Utility Funvtions
void Dx::StartUp(float width, float height, bool is_vsync, bool is_fullscreen)
{
	CreateDeviceAndSwapchain(width, height, is_vsync, is_fullscreen);
	CreateDepthStencilandRasterState();
	InitPipelineStages();
	CreateViewport(width, height);
}

void Dx::ShutDown()
{
	 render_target->Release();
	 depthStencilBuffer->Release();
	// depthStencilState->Release();
	 depthStencilView->Release();
	// rasterState->Release();
	 delete viewport;
	 backBuffer->Release();
	 deviceContext->Release();
	 swapchain->Release();
	 device->Release();
}