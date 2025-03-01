// VCuber.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "VCuber.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_VCUBER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//Console window
#ifndef NDEBUG
	AllocConsole();
	FILE* new_std_in_out;
	freopen_s(&new_std_in_out, "CONOUT$", "w", stdout);
	freopen_s(&new_std_in_out, "CONIN$", "r", stdin);
	std::cout << "VCuber!\n";

#endif

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VCUBER));

	MSG msg;

	//Init
	Dx *directX = new Dx;
	Vr *vive = new Vr;
	Scene *scene = nullptr;
	isVR = vive->VrInit(0.1f, 1000.0f);

	if (isVR)
	{
		directX->StartUp(vive->GetRecommendedDisplayWidth(), vive->GetRecommendedDisplayHeight(), true, false);
		scene = new Scene(directX, isVR, vive->GetRecommendedDisplayWidth(), vive->GetRecommendedDisplayHeight());
		vive->SetVRCameras();
	}
	else
	{

		directX->StartUp(1280, 720, true, false);
		scene = new Scene(directX, isVR, 1280, 720);
	}

	Actions actions;
	VRInput vrInput;
	// Main message loop:
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Update
		if (isVR)
		{
			scene->Update();
			vive->UpdateHMDMatrixPose();
			if (vive->GetHmd()->GetControllerState(vive->leftController, &vive->controller, sizeof(vive->controller)))
			{
				vrInput.user = true;
				if (vive->controller.ulButtonPressed == 4294967296)
				{
					if (vive->controller.rAxis[0].x > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.D = true;
					}
					else if (vive->controller.rAxis[0].x < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.D1 = true;
					}
					else if (vive->controller.rAxis[0].y > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.L1 = true;
					}
					else if (vive->controller.rAxis[0].y < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.L = true;
					}
					else
					{
						vrInput.LtrackC = true;
					}

				}
				else if (vive->controller.ulButtonPressed == 4)
				{
					if (vive->controller.rAxis[0].y > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.B1 = true;
					}
					else if (vive->controller.rAxis[0].y < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.B = true;
					}
				}
				else if (vive->controller.ulButtonPressed == 2)
				{
					vrInput.ResetNonToggles();
					vrInput.LButton1 = true;
				}
				else
				{
					vrInput._isPressedL = false;
				}
				if (vive->controller.rAxis[0].x > 0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.LtrackR = true;
				}
				else if (vive->controller.rAxis[0].x < -0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.LtrackL = true;
				}
				else if (vive->controller.rAxis[0].y > 0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.LtrackU = true;
				}
				else if (vive->controller.rAxis[0].y < -0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.LtrackD = true;
				}
			}

			if (vive->GetHmd()->GetControllerState(vive->rightController, &vive->controller, sizeof(vive->controller)))
			{
				if (vive->controller.ulButtonPressed == 4294967296)
				{
					if (vive->controller.rAxis[0].x > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.U1 = true;
					}
					else if (vive->controller.rAxis[0].x < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.U = true;
					}
					else if (vive->controller.rAxis[0].y > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.R = true;
					}
					else if (vive->controller.rAxis[0].y < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.R1 = true;
					}
					else
					{
						vrInput.RtrackC = true;
					}
				}
				else if (vive->controller.ulButtonPressed == 4)
				{
					if (vive->controller.rAxis[0].y > 0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.F1 = true;
					}
					else if (vive->controller.rAxis[0].y < -0.5f)
					{
						vrInput.ResetNonToggles();
						vrInput.F = true;
					}
				}
				else if (vive->controller.ulButtonPressed == 2 && vrInput.RButton1Toggle)
				{
					vrInput.RButton1 = !vrInput.RButton1;
					vrInput.RButton1Toggle = false;
				}
				else
				{
					vrInput._isPressedR = false;
					vrInput.RButton1Toggle = true;
				}
				if (vive->controller.rAxis[0].x > 0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.RtrackR = true;
				}
				else if (vive->controller.rAxis[0].x < -0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.RtrackL = true;
				}
				else if (vive->controller.rAxis[0].y > 0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.RtrackU = true;
				}
				else if (vive->controller.rAxis[0].y < -0.5f)
				{
					vrInput.ResetNonToggles();
					vrInput.RtrackD = true;
				}

			}
			scene->MoveUpdate(vrInput);
			vive->leftEyeTex2D = &scene->VrUpdate(DirectX::XMMatrixIdentity(), vive->mat4controllerPoseLeft, vive->mat4controllerPoseRight, vive->GetMatrixWorldViewEye(vr::Eye_Left), vive->GetHMDMatrixProjectionEye(vr::Eye_Left), vr::Eye_Left);
			vive->rightEyeTex2D = &scene->VrUpdate(DirectX::XMMatrixIdentity(), vive->mat4controllerPoseLeft, vive->mat4controllerPoseRight, vive->GetMatrixWorldViewEye(vr::Eye_Right), vive->GetHMDMatrixProjectionEye(vr::Eye_Right), vr::Eye_Right);
			vive->PresentToVr(vive->leftEyeTex2D, vive->rightEyeTex2D);
		}
		else
			scene->Update();
	}

	//Shutdown
	vive->VrShutDown();
	directX->ShutDown();
	delete directX;
	return (int)msg.wParam;
}

#pragma region stuff
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VCUBER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_VCUBER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
#pragma endregion