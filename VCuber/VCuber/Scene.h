#pragma once
#include "stdafx.h"
#include "Animator.h"
#include "InputTranslator.h"
#include "MeshLoader.h"
#include "Object.h"
#include "ShaderLoader.h"
#include "Debugger.h"
class Scene
{
	//Graphics setup
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX cubeWorld = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX camera = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX wvp = DirectX::XMMatrixIdentity();
	float aspectRatio = 0.0f;
	float FoV = 0.0f;
	float nearP = 0.0f;
	float farP = 0.0f;
	float width = 1280;
	float height = 720;
	Dx* directX = nullptr;
	ID3D11Buffer *worldViewProjection = nullptr;
	ID3D11Buffer *testVertexBuffer = nullptr;
	ID3D11Buffer *testVertexBuffer1 = nullptr;
	ID3D11RasterizerState *rasterState = nullptr;
	ShaderLoader *shaderLoader = nullptr;

	//Texture stuff for objects
	ID3D11Texture2D* defaultTexture;
	ID3D11ShaderResourceView* defaultTextureSRV;
	ID3D11Texture2D* screenTexture;
	std::vector<ID3D11ShaderResourceView*> stepsSRV;
	ID3D11Texture2D* gripTexture;
	std::vector<ID3D11ShaderResourceView*> gripSRV;
	ID3D11SamplerState* texSamplerState;
	ID3D11SamplerState* clampSamplestate;
	std::vector<wchar_t*> screenImages;
	bool isVR = false;
	MeshLoader meshloader;
	DebugInput debugInput;
	VRInput vrInput;
	std::vector<std::string> meshList;
	std::vector<Object> objects;
	std::vector<Object> leftGrip;
	std::vector<Object> rightGrip;
	std::vector<Object> sceneMeshes;
	Object *testObj = nullptr; 
	Object *testObj1 = nullptr;
	Object *testObj2 = nullptr;
	Object *screenObj = nullptr;
	Pointer resetFace;
	CubeTranslator cubeTranslator;
	CubeDebugger debugger = CubeDebugger();
	//Logical representation of mesh
	CubeGraph solvedGraphicsCube = CubeGraph(Face(1, 2, 3, 10, 11, 12, 18, 22, 23), Face(18, 22, 23, 24, 19, 25, 20, 21, 26), Face(23, 12, 3, 25, 14, 6, 26, 17, 9), Face(3, 2, 1, 6, 5, 4, 9, 8, 7), Face(1, 10, 18, 4, 0, 24, 7, 15, 20), Face(20, 21, 26, 15, 16, 17, 7, 8, 9));
	CubeGraph graphicsCube = CubeGraph(Face(1, 2, 3, 10, 11, 12, 18, 22, 23), Face(18, 22, 23, 24, 19, 25, 20, 21, 26), Face(23, 12, 3, 25, 14, 6, 26, 17, 9), Face(3, 2, 1, 6, 5, 4, 9, 8, 7), Face(1, 10, 18, 4, 0, 24, 7, 15, 20), Face(20, 21, 26, 15, 16, 17, 7, 8, 9));
	//Logical representation of rubik's cube (For AI and debugger)
	CubeGraph cube = CubeGraph();
	//Cube AI
	AI radar = AI(graphicsCube, cube, solvedGraphicsCube);
	Face turningFace = Face(1);
	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3(0, 0, 0);
	DirectX::XMFLOAT3 translation = DirectX::XMFLOAT3(0, 0, 0);
	bool isTurning = false;
	bool isMoving = false;
	bool leftSnap = false;
	bool rightSnap = false;
	bool aiSolve = false;
	int frameCount = 0;
	int rotationAngle = 90;
	int rotationScale = 2;
	float moveDistance = 0.05f;
	float movescale = 0.005;
	int center = 0;
	int helpStep = 0;
	int helpStepindxcount = 6;
public:
//	CubeGraph graphicsCube = *tempGraphicsCube;
	//Graphics Setup varibles for VR
	ID3D11Texture2D * leftEyeTex2D, *rightEyeTex2D;
	ID3D11RenderTargetView *leftEyeRenderTarget, *rightEyeRenderTarget;
	ID3D11ShaderResourceView *leftEyeSRV, *rightEyeSRV;
	Scene(Dx* dx, bool vr, float width, float height)
	{
		Init(dx, vr, width, height);
	};
	~Scene()
	{
		ShutDown();
	}
	void AIMove(VRInput _move);
	void Init(Dx* dx, bool vr, float width = 1280, float height = 720);
	void CameraAndViewSetup();
	void CreateObject();
	void ClearScreen();
	void SceneBuffers();
	void Update();
	void MoveUpdate(VRInput &_movelist);
	ID3D11Texture2D& VrUpdate(DirectX::XMMATRIX model, DirectX::XMMATRIX leftControl, DirectX::XMMATRIX rightControl, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, UINT eye);
	void RenderToDebug();
	void RenderToVR(DirectX::XMMATRIX model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, DirectX::XMMATRIX leftControl, DirectX::XMMATRIX rightControl, UINT stride, UINT offset);
	void Draw(DirectX::XMMATRIX wvp, Object *_object, UINT *_stride, UINT offset);
	void ShutDown();
	Face GetFaceParents(Pointer current, int _face);
};
struct WorldData
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;

	WorldData()
	{
		DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixIdentity());
		DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixIdentity());
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixIdentity());
	}

};
