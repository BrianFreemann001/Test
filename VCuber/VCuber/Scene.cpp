#include "stdafx.h"
#include "Scene.h"
#include "BasicPixelShader.csh"
#include "BasicVertexShader.csh"
#include "WICTextureLoader.h"


void Scene::AIMove(VRInput _move)
{
	if (radar.currentMove < radar.movelist.size() || isTurning)
	{
		if (!isTurning)
		{
			MoveUpdate(_move);
			radar.currentMove += 1;
		}
		else if (isTurning)
		{
			MoveUpdate(radar.waiting);
		}
	}
	else if (!(radar.currentMove < radar.movelist.size()) && !isTurning)
	{
		radar.currentMove = 0;
		aiSolve = false;
	}
}

void Scene::Init(Dx* dx, bool vr, float width, float height)
{
	directX = dx;
	isVR = vr;
	this->width = width;
	this->height = height;
	shaderLoader = new ShaderLoader(directX);
	CameraAndViewSetup();
	SceneBuffers();

	D3D11_RASTERIZER_DESC rsdesc;
	rsdesc.FillMode = D3D11_FILL_SOLID;
	rsdesc.CullMode = D3D11_CULL_NONE;
	rsdesc.DepthClipEnable = true;
	rsdesc.AntialiasedLineEnable = false;
	rsdesc.DepthBias = 0;
	rsdesc.DepthBiasClamp = 0.0f;
	rsdesc.FrontCounterClockwise = false;
	rsdesc.MultisampleEnable = false;
	rsdesc.ScissorEnable = false;
	rsdesc.SlopeScaledDepthBias = false;
	directX->device->CreateRasterizerState(&rsdesc, &rasterState);
	debugger.ClearConsole();
	debugger.Keys();
	debugger.ShowCenterList(cube);
	debugger.ShowFaces(cube, "Colour Cube");
	debugger.ShowFaces(graphicsCube, "Graphics Cube");
	debugger.ShowFaces(radar.GetColourCube(), "Bot Colour Cube");
	debugger.ShowFaces(radar.GetGraphicsCube(), "Bot Graphics Cube");
	cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
	cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixTranslation(0.0f, 1.50f, 0.0f));
}

void Scene::CameraAndViewSetup()
{
	aspectRatio = width / height;
	FoV = 70.0f * DirectX::XM_PI / 180.0f;
	nearP = 0.001f;
	farP = 10000.0f;
	if (aspectRatio < 1.0f)
	{
		FoV *= 2.0f;
	}

	DirectX::XMMATRIX perspectiveMatrix = DirectX::XMMatrixPerspectiveFovLH(FoV, aspectRatio, nearP, farP);

	DirectX::XMMATRIX orientationMatrix = DirectX::XMMatrixIdentity();

	projection = (perspectiveMatrix * orientationMatrix);

	static const DirectX::XMVECTORF32 eye = { 0.0f, 1.0f, -10.5f, 0.0f };
	static const DirectX::XMVECTORF32 at = { 0.0f, 1.0f, 1.0f, 0.0f };
	static const DirectX::XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	camera = XMMatrixLookAtLH(eye, at, up);
}


void Scene::CreateObject()
{

	std::string modelPath;
#pragma region getting cube mesh list
	meshList = meshloader.GetMeshList("MeshList.ral");
	//Subtracting 1 because meshlist contains extra entery"
	if (meshList.size() > 0)
		objects.resize(meshList.size() - 1);
	for (int i = 0; i < objects.size(); i++)
	{
		modelPath = "Models/";
		modelPath.append(meshList[i].c_str());
		objects[i].objMesh = meshloader.ReadMesh(modelPath.c_str());
		objects[i].SetName(meshList[i]);

		D3D11_SUBRESOURCE_DATA meshBufferData = { 0 };
		meshBufferData.pSysMem = objects[i].objMesh.verts.data();
		meshBufferData.SysMemPitch = 0;
		meshBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC meshBufferDesc(sizeof(Vertex) * objects[i].objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
		directX->device->CreateBuffer(&meshBufferDesc, &meshBufferData, &objects[i].vertexBuffer);
		DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Rubiks_colors.png", (ID3D11Resource**)objects[i].diffuseTexture, &objects[i].diffuseTextureSRV);
	}
#pragma endregion
#pragma region getting left and right grip mesh list
	meshList = meshloader.GetMeshList("LGripMeshList.ral");
	if (meshList.size() > 0)
		leftGrip.resize(meshList.size() - 1);
	for (int i = 0; i < leftGrip.size(); i++)
	{
		modelPath = "Models/";
		modelPath.append(meshList[i].c_str());
		leftGrip[i].objMesh = meshloader.ReadMesh(modelPath.c_str());
		leftGrip[i].SetName(meshList[i]);

		D3D11_SUBRESOURCE_DATA leftGripBufferData = { 0 };
		leftGripBufferData.pSysMem = leftGrip[i].objMesh.verts.data();
		leftGripBufferData.SysMemPitch = 0;
		leftGripBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC leftGripBufferDesc(sizeof(Vertex) * leftGrip[i].objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
		directX->device->CreateBuffer(&leftGripBufferDesc, &leftGripBufferData, &leftGrip[i].vertexBuffer);
	}
	meshList = meshloader.GetMeshList("RGripMeshList.ral");
	if (meshList.size() > 0)
		rightGrip.resize(meshList.size() - 1);
	for (int i = 0; i < rightGrip.size(); i++)
	{
		modelPath = "Models/";
		modelPath.append(meshList[i].c_str());
		rightGrip[i].objMesh = meshloader.ReadMesh(modelPath.c_str());
		rightGrip[i].SetName(meshList[i]);

		D3D11_SUBRESOURCE_DATA rightGripBufferData = { 0 };
		rightGripBufferData.pSysMem = rightGrip[i].objMesh.verts.data();
		rightGripBufferData.SysMemPitch = 0;
		rightGripBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC rightGripBufferDesc(sizeof(Vertex) * rightGrip[i].objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
		directX->device->CreateBuffer(&rightGripBufferDesc, &rightGripBufferData, &rightGrip[i].vertexBuffer);
	}
#pragma endregion 

	meshList = meshloader.GetMeshList("Scene1MeshList.ral");
	if (meshList.size() > 0)
		sceneMeshes.resize(meshList.size() - 1);
	for (int i = 0; i < sceneMeshes.size(); i++)
	{
		modelPath = "Models/VCuberScene/";
		modelPath.append(meshList[i].c_str());
		sceneMeshes[i].objMesh = meshloader.ReadMesh(modelPath.c_str());
		sceneMeshes[i].SetName(meshList[i]);

		D3D11_SUBRESOURCE_DATA sceneMeshesBufferData = { 0 };
		sceneMeshesBufferData.pSysMem = sceneMeshes[i].objMesh.verts.data();
		sceneMeshesBufferData.SysMemPitch = 0;
		sceneMeshesBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC sceneMeshesBufferDesc(sizeof(Vertex) * sceneMeshes[i].objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
		directX->device->CreateBuffer(&sceneMeshesBufferDesc, &sceneMeshesBufferData, &sceneMeshes[i].vertexBuffer);
		DirectX::CreateWICTextureFromFile(directX->device, L"Textures/grey.jpg", (ID3D11Resource**)sceneMeshes[i].diffuseTexture, &sceneMeshes[i].diffuseTextureSRV);
	}

	testObj->objMesh = meshloader.ReadMesh("LeftHand.rad");

	D3D11_SUBRESOURCE_DATA meshBufferData = { 0 };
	meshBufferData.pSysMem = testObj->objMesh.verts.data();
	meshBufferData.SysMemPitch = 0;
	meshBufferData.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC meshBufferDesc(sizeof(Vertex) * testObj->objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
	directX->device->CreateBuffer(&meshBufferDesc, &meshBufferData, &testObj->vertexBuffer);

	testObj1->objMesh = meshloader.ReadMesh("RightHand.rad");

	D3D11_SUBRESOURCE_DATA meshBufferData1 = { 0 };
	meshBufferData1.pSysMem = testObj1->objMesh.verts.data();
	meshBufferData1.SysMemPitch = 0;
	meshBufferData1.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC meshBufferDesc1(sizeof(Vertex) * testObj1->objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
	directX->device->CreateBuffer(&meshBufferDesc1, &meshBufferData1, &testObj1->vertexBuffer);

	testObj2->objMesh = meshloader.ReadMesh("pCube1");

	D3D11_SUBRESOURCE_DATA meshBufferData2 = { 0 };
	meshBufferData2.pSysMem = testObj2->objMesh.verts.data();
	meshBufferData2.SysMemPitch = 0;
	meshBufferData2.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC meshBufferDesc2(sizeof(Vertex) * testObj2->objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
	directX->device->CreateBuffer(&meshBufferDesc2, &meshBufferData2, &testObj2->vertexBuffer);

	screenObj->objMesh = meshloader.ReadMesh("screen");

	D3D11_SUBRESOURCE_DATA meshBufferData3 = { 0 };
	meshBufferData3.pSysMem = screenObj->objMesh.verts.data();
	meshBufferData3.SysMemPitch = 0;
	meshBufferData3.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC meshBufferDesc3(sizeof(Vertex) * screenObj->objMesh.verts.size(), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
	directX->device->CreateBuffer(&meshBufferDesc3, &meshBufferData3, &screenObj->vertexBuffer);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Hand.jpg", (ID3D11Resource**)testObj->diffuseTexture, &testObj->diffuseTextureSRV);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Hand.jpg", (ID3D11Resource**)testObj1->diffuseTexture, &testObj1->diffuseTextureSRV);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Floor.jpg", (ID3D11Resource**)testObj2->diffuseTexture, &testObj2->diffuseTextureSRV);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Floor.jpg", (ID3D11Resource**)defaultTexture, &defaultTextureSRV);
	stepsSRV.resize((helpStepindxcount + 1));
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Controller input.png", (ID3D11Resource**)screenTexture, &stepsSRV[0]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps0.png", (ID3D11Resource**)screenTexture, &stepsSRV[1]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps1.png", (ID3D11Resource**)screenTexture, &stepsSRV[2]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps2.png", (ID3D11Resource**)screenTexture, &stepsSRV[3]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps3.png", (ID3D11Resource**)screenTexture, &stepsSRV[4]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps4.png", (ID3D11Resource**)screenTexture, &stepsSRV[5]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/Steps5.png", (ID3D11Resource**)screenTexture, &stepsSRV[6]);
	gripSRV.resize(5);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/GripNeutral.png", (ID3D11Resource**)gripTexture, &gripSRV[0]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/GripUp.png", (ID3D11Resource**)gripTexture, &gripSRV[1]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/GripRight.png", (ID3D11Resource**)gripTexture, &gripSRV[2]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/GripDown.png", (ID3D11Resource**)gripTexture, &gripSRV[3]);
	DirectX::CreateWICTextureFromFile(directX->device, L"Textures/GripLeft.png", (ID3D11Resource**)gripTexture, &gripSRV[4]);
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	directX->device->CreateSamplerState(&sampDesc, &texSamplerState);
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	directX->device->CreateSamplerState(&sampDesc, &clampSamplestate);
}

void Scene::ClearScreen()
{
	directX->deviceContext->ClearRenderTargetView(directX->render_target, DirectX::Colors::RoyalBlue);
	directX->deviceContext->ClearDepthStencilView(directX->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Scene::SceneBuffers()
{

	testObj = new Object();
	testObj1 = new Object();
	testObj2 = new Object();
	screenObj = new Object();
	CreateObject();

	D3D11_INPUT_ELEMENT_DESC layout[]
	{

	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	//TODO: Apply shader creation to Shader class and use that to choose shaders
	directX->device->CreateInputLayout(layout, ARRAYSIZE(layout), basicVertexShader, sizeof(basicVertexShader), &testObj->objShaders->inputLayout);
	directX->device->CreateVertexShader(basicVertexShader, sizeof(basicVertexShader), NULL, &testObj->objShaders->vertexShader);
	directX->device->CreatePixelShader(basicPixelShader, sizeof(basicPixelShader), NULL, &testObj->objShaders->pixelShader);
	testObj1->objShaders->vertexShader = testObj->objShaders->vertexShader;
	testObj1->objShaders->pixelShader = testObj->objShaders->pixelShader;
	testObj2->objShaders->vertexShader = testObj->objShaders->vertexShader;
	testObj2->objShaders->pixelShader = testObj->objShaders->pixelShader;
	screenObj->objShaders->vertexShader = testObj->objShaders->vertexShader;
	screenObj->objShaders->pixelShader = testObj->objShaders->pixelShader;
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].objShaders->inputLayout = testObj->objShaders->inputLayout;
		objects[i].objShaders->vertexShader = testObj->objShaders->vertexShader;
		objects[i].objShaders->pixelShader = testObj->objShaders->pixelShader;
	}
	for (int i = 0; i < leftGrip.size(); i++)
	{
		leftGrip[i].objShaders->inputLayout = testObj->objShaders->inputLayout;
		leftGrip[i].objShaders->vertexShader = testObj->objShaders->vertexShader;
		leftGrip[i].objShaders->pixelShader = testObj->objShaders->pixelShader;
	}
	for (int i = 0; i < rightGrip.size(); i++)
	{
		rightGrip[i].objShaders->inputLayout = testObj->objShaders->inputLayout;
		rightGrip[i].objShaders->vertexShader = testObj->objShaders->vertexShader;
		rightGrip[i].objShaders->pixelShader = testObj->objShaders->pixelShader;
	}
	for (int i = 0; i < sceneMeshes.size(); i++)
	{
		sceneMeshes[i].objShaders->inputLayout = testObj->objShaders->inputLayout;
		sceneMeshes[i].objShaders->vertexShader = testObj->objShaders->vertexShader;
		sceneMeshes[i].objShaders->pixelShader = testObj->objShaders->pixelShader;
	}
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(DirectX::XMMATRIX), D3D11_BIND_CONSTANT_BUFFER);
	directX->device->CreateBuffer(&constantBufferDesc, nullptr, &worldViewProjection);

	//Creating texture buffer/eye for hmd
	if (isVR)
	{

		D3D11_TEXTURE2D_DESC vrtextureDesc;

		D3D11_RENDER_TARGET_VIEW_DESC vrrenderTargetViewDesc;
		ZeroMemory(&vrrenderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		D3D11_SHADER_RESOURCE_VIEW_DESC vrshaderResourceViewDesc;
		ZeroMemory(&vrshaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		//Zeroing texture desc and filling in data that corresponds to vr::Eye data
		ZeroMemory(&vrtextureDesc, sizeof(vrtextureDesc));

		vrtextureDesc.Width = (UINT)width;
		vrtextureDesc.Height = (UINT)height;
		vrtextureDesc.MipLevels = 1;
		vrtextureDesc.ArraySize = 1;
		vrtextureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		vrtextureDesc.SampleDesc.Count = 1;
		vrtextureDesc.Usage = D3D11_USAGE_DEFAULT;
		vrtextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		vrtextureDesc.CPUAccessFlags = 0;
		vrtextureDesc.MiscFlags = 0;

		directX->device->CreateTexture2D(&vrtextureDesc, NULL, &leftEyeTex2D);
		directX->device->CreateTexture2D(&vrtextureDesc, NULL, &rightEyeTex2D);

		//Setting rt desc
		vrrenderTargetViewDesc.Format = vrtextureDesc.Format;
		vrrenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		vrrenderTargetViewDesc.Texture2D.MipSlice = 0;
		//Creating render target for each eye
		directX->device->CreateRenderTargetView(leftEyeTex2D, &vrrenderTargetViewDesc, &leftEyeRenderTarget);
		directX->device->CreateRenderTargetView(rightEyeTex2D, &vrrenderTargetViewDesc, &rightEyeRenderTarget);
		//Setting srv desc
		vrshaderResourceViewDesc.Format = vrtextureDesc.Format;
		vrshaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		vrshaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		vrshaderResourceViewDesc.Texture2D.MipLevels = 1;
		//Creating srv
		directX->device->CreateShaderResourceView(leftEyeTex2D, &vrshaderResourceViewDesc, &leftEyeSRV);
		directX->device->CreateShaderResourceView(rightEyeTex2D, &vrshaderResourceViewDesc, &rightEyeSRV);
	}
}

void Scene::Update()
{
	ClearScreen();
	RenderToDebug();
#pragma region Debug Input
	if (GetAsyncKeyState(VK_RBUTTON) && GetAsyncKeyState('W'))
	{
		camera = debugInput.ZoomIn(camera);
	}
	if (GetAsyncKeyState(VK_RBUTTON) && GetAsyncKeyState('S'))
	{
		camera = debugInput.ZoomOut(camera);
	}
	if (GetAsyncKeyState('W') && !GetAsyncKeyState(VK_RBUTTON))
	{
		camera = debugInput.PanUp(camera);
	}
	if (GetAsyncKeyState('A'))
	{
		camera = debugInput.PanLeft(camera);
	}
	if (GetAsyncKeyState('S') && !GetAsyncKeyState(VK_RBUTTON))
	{
		camera = debugInput.PanDown(camera);
	}
	if (GetAsyncKeyState('D'))
	{
		camera = debugInput.PanRight(camera);
	}
	camera = debugInput.Look(camera);
#pragma endregion
}

void Scene::MoveUpdate(VRInput &_movelist)
{
	//Setting grip texture
	for (int i = 0; i < leftGrip.size(); i++)
	{
		leftGrip[i].diffuseTextureSRV = gripSRV[0];
	}
	if (_movelist.LtrackL)
	{
		leftGrip[2].diffuseTextureSRV = gripSRV[2];
		_movelist.LtrackL = false;
	}
	else if (_movelist.LtrackR)
	{
		leftGrip[2].diffuseTextureSRV = gripSRV[4];
		_movelist.LtrackR = false;
	}
	else if (_movelist.LtrackD && !_movelist.B)
	{
		leftGrip[2].diffuseTextureSRV = gripSRV[3];
		_movelist.LtrackD = false;
	}
	if (_movelist.LtrackU && !_movelist.B1)
	{
		leftGrip[1].diffuseTextureSRV = gripSRV[1];
		_movelist.LtrackU = false;
	}
	if (_movelist.LtrackD && _movelist.B)
	{
		leftGrip[0].diffuseTextureSRV = gripSRV[4];
		_movelist.LtrackD = false;
	}
	else if (_movelist.LtrackU && _movelist.B1)
	{
		leftGrip[0].diffuseTextureSRV = gripSRV[2];
		_movelist.LtrackU = false;
	}

	for (int i = 0; i < rightGrip.size(); i++)
	{
		rightGrip[i].diffuseTextureSRV = gripSRV[0];
	}
	if (_movelist.RtrackL)
	{
		rightGrip[1].diffuseTextureSRV = gripSRV[2];
		_movelist.RtrackL = false;
	}
	else if (_movelist.RtrackU && !_movelist.F1)
	{
		rightGrip[1].diffuseTextureSRV = gripSRV[1];
		_movelist.RtrackU = false;
	}
	else if (_movelist.RtrackR)
	{
		rightGrip[1].diffuseTextureSRV = gripSRV[4];
		_movelist.RtrackR = false;
	}
	if (_movelist.RtrackD && !_movelist.F)
	{
		rightGrip[2].diffuseTextureSRV = gripSRV[3];
		_movelist.RtrackD = false;
	}
	if (_movelist.RtrackD && _movelist.F)
	{
		rightGrip[0].diffuseTextureSRV = gripSRV[4];
		_movelist.RtrackD = false;
	}
	else if (_movelist.RtrackU && _movelist.F1)
	{
		rightGrip[0].diffuseTextureSRV = gripSRV[2];
		_movelist.RtrackU = false;
	}
	//TODO: Use to if check toggle input access VRInput.user
	if (true)
	{
		if (!_movelist._isPressedL)
		{
			if (_movelist.LButton1)
			{
				helpStep = 0;
				radar.SetColourCube(cube);
				radar.SetGraphicsCube(graphicsCube);
				if (!radar.StateSolved())
					radar.Solve(radar.Evaluate());
				if (radar.movelist.size() == 0)
					radar.GetSolveVRInput();
				aiSolve = true;
				_movelist.LButton1 = false;
			}
			if (_movelist.LtrackC && !_movelist.RtrackC)
			{

				_movelist.LtrackButton = !_movelist.LtrackButton;
				_movelist.LtrackC = false;
			}
			if (!isTurning)
			{

				if (_movelist.D)
				{
					cubeTranslator.TurnDownCW(cube);
					cubeTranslator.TurnDownCW(graphicsCube);
					turningFace = GetFaceParents(resetFace, 5);
					center = turningFace.face[1][1];
					rotation = DirectX::XMFLOAT3(0, DirectX::XMConvertToRadians(rotationScale), 0);
					_movelist.D = false;
					_movelist.LtrackR = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.D1)
				{
					cubeTranslator.TurnDownCCW(cube);
					cubeTranslator.TurnDownCCW(graphicsCube);
					turningFace = GetFaceParents(resetFace, 5);
					center = turningFace.face[1][1];
					rotation = DirectX::XMFLOAT3(0, DirectX::XMConvertToRadians(-rotationScale), 0);
					_movelist.D1 = false;
					_movelist.LtrackL = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.L)
				{
					cubeTranslator.TurnLeftCW(cube);
					cubeTranslator.TurnLeftCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 4);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(rotationScale), 0, 0);
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(rotationScale));
					_movelist.L = false;
					_movelist.LtrackD = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.L1)
				{
					cubeTranslator.TurnLeftCCW(cube);
					cubeTranslator.TurnLeftCCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 4);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(-rotationScale), 0, 0);
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(-rotationScale));
					_movelist.L1 = false;
					_movelist.LtrackU = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.B)
				{
					cubeTranslator.TurnBackCCW(cube);
					cubeTranslator.TurnBackCCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 3);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(-rotationScale));
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(-rotationScale), 0, 0);
					_movelist.B = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.B1)
				{
					cubeTranslator.TurnBackCW(cube);
					cubeTranslator.TurnBackCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 3);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(rotationScale));
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(rotationScale), 0, 0);
					_movelist.B1 = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.rotateLeft)
				{
					cube.point = cubeTranslator.GetLeft(cube.point);
					graphicsCube.point = cubeTranslator.GetLeft(graphicsCube.point);
					_movelist.rotateLeft = false;
					//	debugger.update = true;
					//TODO:	update when you make an animation for this
					//	isTurning = true;
				}
			}
		}
		if (isTurning)
		{

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{

					objects[turningFace.face[i][j]].SetTransform((DirectX::XMMatrixMultiply(objects[turningFace.face[i][j]].GetTransform(), DirectX::XMMatrixRotationRollPitchYaw((float)rotation.x, (float)rotation.y, (float)rotation.z))));
				}
			}
			if (debugger.update)
			{

				debugger.ClearConsole();
				debugger.Keys();
				debugger.ShowCenterList(cube);
				debugger.ShowFaces(cube, "Colour Cube");
				debugger.ShowFaces(graphicsCube, "Graphics Cube");
				debugger.ShowFaces(radar.GetColourCube(), "Bot Colour Cube");
				debugger.ShowFaces(radar.GetGraphicsCube(), "Bot Graphics Cube");
				debugger.update = false;
			}
			frameCount += 1;
			if (frameCount == rotationAngle / rotationScale)
			{
				isTurning = false;
				frameCount = 0;
			}
		}

		if (isMoving)
		{
			//TODO: Set grip movement mechanic here

		}
		_movelist._isPressedL = true;
		leftSnap = _movelist.LtrackButton;

		if (!_movelist._isPressedR)
		{
			if (!_movelist.LtrackC && _movelist.RtrackC)
			{

				_movelist.RtrackButton = !_movelist.RtrackButton;
				_movelist.RtrackC = false;
			}
			else if (_movelist.RButton1)
			{
				if (_movelist.U)
				{
					if (helpStep == 0)
					{
						helpStep = helpStepindxcount;
					}
					else
						helpStep -= 1;
					_movelist.U = false;
				}
				else if (_movelist.U1)
				{
					if (helpStep == helpStepindxcount)
					{
						helpStep = 0;
					}
					else
						helpStep += 1;
					_movelist.U1 = false;
				}
			}
			else if (!isTurning)
			{
				if (_movelist.U)
				{
					cubeTranslator.TurnUpCW(cube);
					cubeTranslator.TurnUpCW(graphicsCube);
					turningFace = GetFaceParents(resetFace, 0);
					center = turningFace.face[1][1];
					rotation = DirectX::XMFLOAT3(0, DirectX::XMConvertToRadians(-rotationScale), 0);
					_movelist.U = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.U1)
				{
					cubeTranslator.TurnUpCCW(cube);
					cubeTranslator.TurnUpCCW(graphicsCube);
					turningFace = GetFaceParents(resetFace, 0);
					center = turningFace.face[1][1];
					rotation = DirectX::XMFLOAT3(0, DirectX::XMConvertToRadians(rotationScale), 0);
					_movelist.U1 = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.R)
				{
					cubeTranslator.TurnRightCW(cube);
					cubeTranslator.TurnRightCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 2);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(-rotationScale), 0, 0);
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(-rotationScale));
					_movelist.R = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.R1)
				{
					cubeTranslator.TurnRightCCW(cube);
					cubeTranslator.TurnRightCCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 2);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(rotationScale), 0, 0);
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(rotationScale));
					_movelist.R1 = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.F)
				{
					cubeTranslator.TurnFrontCW(cube);
					cubeTranslator.TurnFrontCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 1);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(-rotationScale));
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(-rotationScale), 0, 0);
					_movelist.F = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.F1)
				{
					cubeTranslator.TurnFrontCCW(cube);
					cubeTranslator.TurnFrontCCW(graphicsCube);
					turningFace = GetFaceParents(cube.point, 1);
					center = turningFace.face[1][1];
					if (cube.point.colour == GREEN || cube.point.colour == BLUE)
						rotation = DirectX::XMFLOAT3(0, 0, DirectX::XMConvertToRadians(rotationScale));
					else if (cube.point.colour == WHITE || cube.point.colour == YELLOW)
						rotation = DirectX::XMFLOAT3(DirectX::XMConvertToRadians(rotationScale), 0, 0);
					_movelist.F1 = false;
					debugger.update = true;
					isTurning = true;
				}
				else if (_movelist.rotateRight)
				{
					cube.point = cubeTranslator.GetRight(cube.point);
					graphicsCube.point = cubeTranslator.GetRight(graphicsCube.point);
					_movelist.rotateRight = false;
					//	debugger.update = true;
					//TODO:	update when you make an animation for this
					//	isTurning = true;
				}
				else if (_movelist.resetFront)
				{
					cube.point = resetFace;
					graphicsCube.point = resetFace;
					_movelist.resetFront = false;
					//	debugger.update = true;
					//TODO:	update when you make an animation for this
					//	isTurning = true;
				}
			}
			if (isTurning)
			{

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						objects[turningFace.face[i][j]].SetTransform((DirectX::XMMatrixMultiply(objects[turningFace.face[i][j]].GetTransform(), DirectX::XMMatrixRotationRollPitchYaw((float)rotation.x, (float)rotation.y, (float)rotation.z))));
					}
				}
				if (debugger.update)
				{

					debugger.ClearConsole();
					debugger.Keys();
					debugger.ShowCenterList(cube);
					debugger.ShowFaces(cube, "Colour Cube");
					debugger.ShowFaces(graphicsCube, "Graphics Cube");
					debugger.ShowFaces(radar.GetColourCube(), "Bot Colour Cube");
					debugger.ShowFaces(radar.GetGraphicsCube(), "Bot Graphics Cube");
					debugger.update = false;
				}
				frameCount += 1;
				if (frameCount == rotationAngle / rotationScale)
				{
					isTurning = false;
					frameCount = 0;
				}
			}
			_movelist._isPressedR = true;
			rightSnap = _movelist.RtrackButton;
		}
	}
}
ID3D11Texture2D& Scene::VrUpdate(DirectX::XMMATRIX model, DirectX::XMMATRIX leftControl, DirectX::XMMATRIX rightControl, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, UINT eye)
{
	if (aiSolve)
	{
		if(radar.currentMove < radar.movelist.size())
		AIMove(radar.movelist[radar.currentMove]);
		else if(!(radar.currentMove < radar.movelist.size()) && radar.movelist.size() > 0)
			AIMove(radar.movelist[0]);
	}
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
	model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(0.0f, 1.50f, 0.0f));
	if (eye == 0)
	{
		directX->deviceContext->ClearRenderTargetView(leftEyeRenderTarget, DirectX::Colors::Crimson);
		directX->deviceContext->ClearDepthStencilView(directX->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		directX->deviceContext->OMSetRenderTargets(1, &leftEyeRenderTarget, directX->depthStencilView);
		for (int i = 0; i < objects.size(); i++)
		{
			if (leftSnap)
			{
				cubeWorld = DirectX::XMMatrixIdentity();
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixTranslation(0.075f, -0.05f, 0));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, leftControl);
			}
			else if (rightSnap)
			{
				cubeWorld = DirectX::XMMatrixIdentity();
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixTranslation(-0.075f, -0.05f, 0));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, rightControl);
			}

			wvp = objects[i].GetTransform() * cubeWorld * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &objects[i], &stride, offset);
		}
		for (int i = 0; i < leftGrip.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(0.075f, -0.05f, 0));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
			wvp = model * leftControl *view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &leftGrip[i], &stride, offset);
		}
		for (int i = 0; i < rightGrip.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(-0.075f, -0.05f, 0));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
			wvp = model * rightControl * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &rightGrip[i], &stride, offset);
		}
		for (int i = 0; i < sceneMeshes.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
		//	model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(2, 2, 2));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(12.0f, -10.50f, -12.0f));
			wvp = model * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			if(i == 70)
			sceneMeshes[i].diffuseTextureSRV = stepsSRV[helpStep];
			Draw(wvp, &sceneMeshes[i], &stride, offset);
		}
		/*model = DirectX::XMMatrixIdentity();
		model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(10, 0.1, 10));
		wvp = model * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj2, &stride, offset);*/
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(-0.015, 0.015, 0.015), leftControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(0.015, 0.015, 0.015), rightControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationX(-99), leftControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(28), leftControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationZ(-269.5), leftControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationX(-99), rightControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(28), rightControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationZ(-269.5), rightControl);
		wvp = leftControl * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj, &stride, offset);
		wvp = rightControl * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj1, &stride, offset);
		//screenObj->diffuseTextureSRV = stepsSRV[helpStep];
		//model = DirectX::XMMatrixIdentity();
		//model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.45, 0.15, 0.01));
		//model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(0.0f, 1.50f, -0.50f));
		//wvp = model * view * projection;
		//wvp = DirectX::XMMatrixTranspose(wvp);
		//Draw(wvp, screenObj, &stride, offset);
		return *leftEyeTex2D;
	}
	else if (eye == 1)
	{
		directX->deviceContext->ClearRenderTargetView(rightEyeRenderTarget, DirectX::Colors::Crimson);
		directX->deviceContext->ClearDepthStencilView(directX->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		directX->deviceContext->OMSetRenderTargets(1, &rightEyeRenderTarget, directX->depthStencilView);
		for (int i = 0; i < objects.size(); i++)
		{
			if (leftSnap)
			{
				cubeWorld = DirectX::XMMatrixIdentity();
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixTranslation(0.075f, -0.05f, 0));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, leftControl);
			}
			else if (rightSnap)
			{
				cubeWorld = DirectX::XMMatrixIdentity();
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixTranslation(-0.075f, -0.05f, 0));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
				cubeWorld = DirectX::XMMatrixMultiply(cubeWorld, rightControl);
			}
			wvp = objects[i].GetTransform() *  cubeWorld * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &objects[i], &stride, offset);
		}
		for (int i = 0; i < leftGrip.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(0.075f, -0.05f, 0));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
			wvp = model * leftControl *view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &leftGrip[i], &stride, offset);
		}
		for (int i = 0; i < rightGrip.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.025, 0.025, 0.025));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(-0.075f, -0.05f, 0));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixRotationX(-DirectX::XMConvertToRadians(90)));
			wvp = model * rightControl * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			Draw(wvp, &rightGrip[i], &stride, offset);
		}
		for (int i = 0; i < sceneMeshes.size(); i++)
		{
			model = DirectX::XMMatrixIdentity();
		//	model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(2, 2, 2));
			model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(12.0f, -10.50f, -12.0f));
			wvp = model * view * projection;
			wvp = DirectX::XMMatrixTranspose(wvp);
			if (i == 70)
				sceneMeshes[i].diffuseTextureSRV = stepsSRV[helpStep];
			Draw(wvp, &sceneMeshes[i], &stride, offset);
		}
	/*	model = DirectX::XMMatrixIdentity();
		model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(10, 0.1, 10));
		wvp = model * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj2, &stride, offset);*/
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(-0.015, 0.015, 0.015), leftControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixScaling(0.015, 0.015, 0.015), rightControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationX(-99), leftControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(28), leftControl);
		leftControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationZ(-269.5), leftControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationX(-99), rightControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationY(28), rightControl);
		rightControl = DirectX::XMMatrixMultiply(DirectX::XMMatrixRotationZ(-269.5), rightControl);
		wvp = leftControl * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj, &stride, offset);
		wvp = rightControl * view * projection;
		wvp = DirectX::XMMatrixTranspose(wvp);
		Draw(wvp, testObj1, &stride, offset);
		//screenObj->diffuseTextureSRV = stepsSRV[helpStep];
		//model = DirectX::XMMatrixIdentity();
		//model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixScaling(0.45, 0.15, 0.01));
		//model = DirectX::XMMatrixMultiply(model, DirectX::XMMatrixTranslation(0.0f, 1.50f, -0.50f));
		//wvp = model * view * projection;
		//wvp = DirectX::XMMatrixTranspose(wvp);
		//Draw(wvp, screenObj, &stride, offset);
		return *rightEyeTex2D;
	}
}

void Scene::Draw(DirectX::XMMATRIX _wvp, Object *_object, UINT *_stride, UINT _offset)
{
	directX->deviceContext->UpdateSubresource(worldViewProjection, NULL, NULL, &_wvp, NULL, NULL);
	directX->deviceContext->IASetInputLayout(_object->objShaders->inputLayout);
	directX->deviceContext->IASetVertexBuffers(0, 1, &_object->vertexBuffer, _stride, &_offset);
	directX->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	directX->deviceContext->VSSetShader(_object->objShaders->vertexShader, NULL, NULL);
	directX->deviceContext->VSSetConstantBuffers(0, 1, &worldViewProjection);
	directX->deviceContext->PSSetShader(_object->objShaders->pixelShader, NULL, NULL);
	directX->deviceContext->PSSetShaderResources(0, 1, &_object->diffuseTextureSRV);
	directX->deviceContext->PSSetSamplers(0, 1, &texSamplerState);
	directX->deviceContext->Draw(_object->objMesh.verts.size(), 0);
}

void Scene::RenderToDebug()
{
	world = DirectX::XMMatrixIdentity();
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	world = DirectX::XMMatrixMultiply(world, DirectX::XMMatrixTranslation(0, 1, 2));
	wvp = world * camera * projection;
	wvp = DirectX::XMMatrixTranspose(wvp);
	directX->deviceContext->OMSetRenderTargets(1, &directX->render_target, directX->depthStencilView);

	directX->deviceContext->RSSetState(rasterState);
	for (int i = 0; i < objects.size(); i++)
		Draw(wvp, &objects[i], &stride, offset);
	world = DirectX::XMMatrixIdentity();
	world = DirectX::XMMatrixMultiply(world, DirectX::XMMatrixScaling(10, 0.1, 10));
	wvp = world * camera * projection;
	wvp = DirectX::XMMatrixTranspose(wvp);
	Draw(wvp, testObj2, &stride, offset);
	directX->swapchain->Present(0, 0);
}

//Still under construction
void Scene::RenderToVR(DirectX::XMMATRIX model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, DirectX::XMMATRIX leftControl, DirectX::XMMATRIX rightControl, UINT stride, UINT offset)
{
	wvp = model * view * projection;
	wvp = DirectX::XMMatrixTranspose(wvp);
	for (int i = 0; i < objects.size(); i++)
		Draw(wvp, &objects[i], &stride, offset);
	wvp = leftControl * view * projection;
	wvp = DirectX::XMMatrixTranspose(wvp);
	Draw(wvp, testObj, &stride, offset);
	wvp = rightControl * view * projection;
	wvp = DirectX::XMMatrixTranspose(wvp);
	Draw(wvp, testObj1, &stride, offset);
}

void Scene::ShutDown()
{
	delete shaderLoader;
	delete testObj;
	delete testObj1;
	delete testObj2;
	delete screenObj;
}
//TODO: Move this to Cube translator
Face Scene::GetFaceParents(Pointer current, int _face)
{
	Face face = Face(1);
	if (_face == 4)
	{
		current = cubeTranslator.GetLeft(graphicsCube.point);
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	else if (_face == 2)
	{
		current = cubeTranslator.GetRight(graphicsCube.point);
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	else if (_face == 0)
	{
		current = cubeTranslator.GetUp(graphicsCube.point);
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	else if (_face == 5)
	{
		current = cubeTranslator.GetDown(graphicsCube.point);
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	else if (_face == 1)
	{
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	else if (_face == 3)
	{
		current = cubeTranslator.GetRight(graphicsCube.point);
		current = cubeTranslator.GetRight(current);
		face = cubeTranslator.GetFace(graphicsCube, current.x, current.y);
	}
	return face;
}
