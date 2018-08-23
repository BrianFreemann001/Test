#pragma once
#include "stdafx.h"
#include "../openvr/headers/openvr.h"
class Vr
{

	//variables for projection calculation
	UINT vrcamheight = 720;
	UINT vrcamwidth = 1280;
	
	//Matrices for world view and projection per eye

	vr::IVRSystem *hmd;	//head mounted display
	vr::IVRRenderModels *renderModels;	//Used for access to default render models
	vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];	//Matrices of tracked device positions
	DirectX::XMMATRIX mat4DevicePose[vr::k_unMaxTrackedDeviceCount];	//Storage for hmd position (player position)

	int poseCount;
	int validPoseCount;
	char devClassChar[vr::k_unMaxTrackedDeviceCount];
	std::string strPoseClasses;
public:
	float vrNearP, vrFarP;
	DirectX::XMMATRIX mat4HMDPose;
	DirectX::XMMATRIX mat4eyePosLeft;
	DirectX::XMMATRIX mat4eyePosRight;
	DirectX::XMMATRIX mat4controllerPoseLeft;
	DirectX::XMMATRIX mat4controllerPoseRight;
	DirectX::XMMATRIX mat4ProjectionLeft;
	DirectX::XMMATRIX mat4ProjectionRight;
	DirectX::XMMATRIX worldTransform = DirectX::XMMatrixIdentity();
	ID3D11Buffer* vrMatrixBuffer = nullptr;
	//Graphics Setup varibles
	ID3D11Texture2D  *rightEyeTex2D, *leftEyeTex2D;
	ID3D11RenderTargetView *leftEyeRenderTarget, *rightEyeRenderTarget;
	ID3D11ShaderResourceView *leftEyeSRV, *rightEyeSRV;

	//Controller Input variables

	vr::VRControllerState_t controller;
	vr::TrackedDeviceIndex_t leftController = 3;
	vr::TrackedDeviceIndex_t rightController = 4;

	//	Vr functions
	vr::IVRSystem *GetHmd()
	{
		return hmd;
	}

	DirectX::XMMATRIX GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	DirectX::XMMATRIX GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye);
	DirectX::XMMATRIX GetMatrixWorldViewEye(vr::Hmd_Eye nEye);
	DirectX::XMMATRIX ConvertSteamVRMatrixToDX(const vr::HmdMatrix34_t &matPose);
	DirectX::XMMATRIX ConvertSteamVRMatrixToDXRow(const vr::HmdMatrix34_t &matPose);
	bool VrInit(float _nearPlane, float _farPlane);
	float GetRecommendedDisplayHeight()
	{
		return (float) vrcamheight;
	}
	float GetRecommendedDisplayWidth()
	{
		return (float) vrcamwidth;
	}
	void SetVRCameras();
	void UpdateHMDMatrixPose();
	void PresentToVr(ID3D11Texture2D * _leftEyeTexture2D, ID3D11Texture2D * _rightEyeTexture2D);
	void VrShutDown();
};