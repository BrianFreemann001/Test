#include "stdafx.h"
#include "InputTranslator.h"

DirectX::XMMATRIX DebugInput::PanLeft(DirectX::XMMATRIX _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(speed, 0, 0);
	_camera = DirectX::XMMatrixMultiply( _camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::PanRight(DirectX::XMMATRIX  _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(-speed, 0, 0);
	_camera = DirectX::XMMatrixMultiply(_camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::PanUp(DirectX::XMMATRIX  _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(0, -speed, 0);
	_camera = DirectX::XMMatrixMultiply(_camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::PanDown(DirectX::XMMATRIX  _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(0, speed, 0);
	_camera = DirectX::XMMatrixMultiply(_camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::ZoomIn(DirectX::XMMATRIX  _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(0, 0, -speed);
	_camera = DirectX::XMMatrixMultiply( _camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::ZoomOut(DirectX::XMMATRIX  _camera)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(0, 0, speed);
	_camera = DirectX::XMMatrixMultiply( _camera, translation);
	return _camera;
}

DirectX::XMMATRIX DebugInput::Look(DirectX::XMMATRIX _camera)
{
	//Keeping track of matrix W(Multiplier) values
	float x = _camera.r[3].m128_f32[0];
	float y = _camera.r[3].m128_f32[1];
	float z = _camera.r[3].m128_f32[2];
	float w = _camera.r[3].m128_f32[3];
	GetCursorPos(&nextCursorPosition);

	if (!GetAsyncKeyState(VK_MBUTTON))
	{
		cursorPosition = nextCursorPosition;
	}

	if (cursorPosition.x != nextCursorPosition.x)
	{
		_camera = XMMatrixMultiply( DirectX::XMMatrixRotationY((nextCursorPosition.x - cursorPosition.x) * -speed), _camera);
	}

	if (cursorPosition.y != nextCursorPosition.y)
	{
		_camera = XMMatrixMultiply( DirectX::XMMatrixRotationX(((nextCursorPosition.y - cursorPosition.y) * -speed)), _camera);
	}
	_camera = XMMatrixMultiply( DirectX::XMMatrixRotationZ(0), _camera);

	cursorPosition = nextCursorPosition;
	_camera.r[3].m128_f32[0] = x;
	_camera.r[3].m128_f32[1] = y;
	_camera.r[3].m128_f32[2] = z;
	_camera.r[3].m128_f32[3] = w;
	return _camera;
}

void VRInput::ResetNonToggles()
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
	bool LtrackL = false;
	bool LtrackU = false;
	bool LtrackR = false;
	bool LtrackD = false;
	bool RtrackL = false;
	bool RtrackU = false;
	bool RtrackR = false;
	bool RtrackD = false;
}
