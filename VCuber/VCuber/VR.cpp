#include "stdafx.h"
#include "VR.h"

DirectX::XMMATRIX Vr::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
	if (!hmd)
		return DirectX::XMMATRIX();

	vr::HmdMatrix34_t eyeMatrix = hmd->GetEyeToHeadTransform(nEye);
	DirectX::XMMATRIX matrixObj(
		eyeMatrix.m[0][0], eyeMatrix.m[1][0], eyeMatrix.m[2][0], 0.0,
		eyeMatrix.m[0][1], eyeMatrix.m[1][1], eyeMatrix.m[2][1], 0.0,
		eyeMatrix.m[0][2], eyeMatrix.m[1][2], eyeMatrix.m[2][2], 0.0,
		eyeMatrix.m[0][3], eyeMatrix.m[1][3], eyeMatrix.m[2][3], 1.0f
	);

	return XMMatrixInverse(0, matrixObj);
}

DirectX::XMMATRIX Vr::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
	if (!hmd)
		return DirectX::XMMATRIX();
	// TODO check here
	vr::HmdMatrix44_t mat = hmd->GetProjectionMatrix(nEye, vrNearP, vrFarP);

	return DirectX::XMMATRIX(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);
}

DirectX::XMMATRIX Vr::GetMatrixWorldViewEye(vr::Hmd_Eye nEye)
{
	DirectX::XMMATRIX matMVP;
	if (nEye == vr::Eye_Left)
	{
		matMVP = mat4HMDPose * mat4eyePosLeft;
	}
	else if (nEye == vr::Eye_Right)
	{
		matMVP = mat4HMDPose * mat4eyePosRight;
	}
	return matMVP;
}

DirectX::XMMATRIX Vr::ConvertSteamVRMatrixToDX(const vr::HmdMatrix34_t &matPose)
{
	DirectX::XMMATRIX matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

DirectX::XMMATRIX Vr::ConvertSteamVRMatrixToDXRow(const vr::HmdMatrix34_t &matPose)
{
	DirectX::XMMATRIX matrixObj(
		matPose.m[0][0], matPose.m[0][1], matPose.m[0][2], matPose.m[0][3],
		matPose.m[1][0], matPose.m[1][1], matPose.m[1][2], matPose.m[1][3],
		matPose.m[2][0], matPose.m[2][1], matPose.m[2][2], matPose.m[2][3],
		matPose.m[3][0], matPose.m[3][1], matPose.m[3][2], 1.0f
	);
	return matrixObj;
}

void Vr::SetVRCameras()
{
	mat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left);
	mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
	mat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left);
	mat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right);
}

bool Vr::VrInit(float _nearPlane, float _farPlane)
{
	//Init for VR
	vr::EVRInitError eError = vr::VRInitError_None;

	hmd = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		hmd = NULL;
		return false;
		std::cout << "Vr Hmd not detected";
	}

	hmd->GetRecommendedRenderTargetSize(&vrcamwidth, &vrcamheight);
	vrNearP = _nearPlane;
	vrFarP = _farPlane;
	std::cout << ("width = %d, height = %d", vrcamwidth, vrcamheight);

	renderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);

	if (!renderModels)
	{
		hmd = NULL;
		vr::VR_Shutdown();
		std::cout << "Unable to get rendrmodel interface";
		return false;
	}

	SetVRCameras();
	if (!vr::VRCompositor())
	{
		vr::VR_Shutdown();
		std::cout << ("Compositor initialization failed. See log file for details\n");
		return false;
	}
	return true;
}

void Vr::UpdateHMDMatrixPose()
{
	if (!hmd)
		return;

	vr::EVRCompositorError error = vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	validPoseCount = 0;
	strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (trackedDevicePose[nDevice].bPoseIsValid)
		{
			validPoseCount++;
			mat4DevicePose[nDevice] = ConvertSteamVRMatrixToDX(trackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			if (devClassChar[nDevice] == 0)
			{
				switch (hmd->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        devClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               devClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           devClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_GenericTracker:    devClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: devClassChar[nDevice] = 'T'; break;
				default:                                       devClassChar[nDevice] = '?'; break;
				}
			}
			strPoseClasses += devClassChar[nDevice];
		}
	}

	if (trackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		mat4HMDPose = DirectX::XMMatrixInverse(NULL, mat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd]);
	}
	if (trackedDevicePose[leftController].bPoseIsValid)
	{
		mat4controllerPoseLeft = mat4DevicePose[leftController];
	}
	if (trackedDevicePose[rightController].bPoseIsValid)
	{
		mat4controllerPoseRight = mat4DevicePose[rightController];
	}
	else
	{
		//std::cout << "pose not valid";
	}
}

void Vr::PresentToVr(ID3D11Texture2D * _leftEyeTexture2D, ID3D11Texture2D * _rightEyeTexture2D)
{
	vr::Texture_t leftEyeTexture = { _leftEyeTexture2D, vr::TextureType_DirectX, vr::ColorSpace_Auto };

	vr::EVRCompositorError error1 = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);

	vr::Texture_t rightEyeTexture = { _rightEyeTexture2D, vr::TextureType_DirectX, vr::ColorSpace_Auto };

	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);
	if (error1)
		std::cout << "EVRCompositorError";
}

void Vr::VrShutDown()
{
	if (hmd)
		vr::VR_Shutdown();
}