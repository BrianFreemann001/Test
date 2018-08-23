#pragma once

class DebugInput
{
	float speed = 0.01f;
	POINT cursorPosition;
	POINT nextCursorPosition;
public:
	DirectX::XMMATRIX PanLeft( DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX PanRight(DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX PanUp(DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX PanDown(DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX ZoomIn(DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX ZoomOut(DirectX::XMMATRIX _camera);
	DirectX::XMMATRIX Look(DirectX::XMMATRIX _camera);
};

struct VRInput
{
	bool L = false;
	bool L1 = false;
	bool R = false;
	bool R1 = false;
	bool U = false;  
	bool U1 = false;
	bool D = false;
	bool D1 = false;
	bool F = false;
	bool F1 = false;
	bool B = false;
	bool B1 = false;
	bool rotateRight = false;
	bool rotateLeft = false;
	bool resetFront = false;
	bool LButton1 = false;
	bool RButton1 = false;
	bool RButton1Toggle = true;
	bool _isPressedL = false;
	bool _isPressedR = false;
	bool LtrackL = false;
	bool LtrackU = false;
	bool LtrackR = false;
	bool LtrackD = false;
	bool LtrackC = false;
	bool LtrackButton = false;
	bool RtrackL = false;
	bool RtrackU = false;
	bool RtrackR = false;
	bool RtrackD = false;
	bool RtrackC = false;
	bool RtrackButton = false;
	bool user = false;
	void ResetNonToggles();
};