#pragma once
#include "stdafx.h"
#include "CubeTranslator.h"
struct CubeDebugger
{
	bool update = false;
	void Keys();
	void ShowCenterList(CubeGraph);
	void ShowFaces(CubeGraph, std::string name);
	void ClearConsole()
	{
		std::system("cls");
	}
};