// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include  <DirectXMath.h>
#include <DirectXColors.h>
#include <d3d11.h>
#include <wrl.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
// TODO: reference additional headers your program requires here
#include "DirectX.h"
#define ORANGE 0
#define GREEN 1
#define WHITE 2
#define BLUE 3
#define YELLOW 4
#define RED 5
struct Pointer
{
	//Colour code
	/*Yellow = 0
	Green = 1
	Orange = 2
	Blue = 3
	Red = 4
	White = 5
	*/
	//initial colour code (Green)
	int colour = 1;
	//initial column index
	int x = 1;
	//initial row index
	int y = 0;
};

struct Maths
{
	//2d - 1d array converter
	int From2Dto1D(int x, int y, int width);
	//1d - 2d array converter
	Pointer From1Dto2D(int index, int width, int colour);
};

struct Actions
{
	bool turnRight = false;
	bool turnLeft = false;
	bool turnUp = false;
	bool turnDown4Watts = false;

	int rightDelta = 0;
	int leftDelta = 0;
	int upDelta = 0;
	int downDelta = 0;
};