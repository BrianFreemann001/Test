#pragma once
#include "stdafx.h"
#include "CubeTranslator.h"
#include "InputTranslator.h"
class AI
{
	CubeGraph botCubeG;
	CubeGraph solvedCubeG;
	CubeGraph botCubeC;
	CubeGraph solvedCubeC;
	std::string fullMovelist, redcrossMovelist, f2lMovelist, ollMovelist, pllMovelist, notSolved;
	CubeTranslator cubeTranslator;
	Pointer resetFace;
public:
	std::vector<VRInput> movelist;
	int currentMove = 0;
	VRInput waiting;
	AI();
	AI(CubeGraph _cube, CubeGraph _colourCube, CubeGraph _solvedGraphicsCube);
	//scans cube and returns an int representing the current solve stage.
	int Evaluate();
	//random scramble
	bool Scramble();
	//input based scramble
	bool Scramble(std::string _scrambleAlg);
	//solve function
	bool Solve(int state);
	//stages
	std::string BottomCross();
	std::string F2L();
	std::string BottomCorners();
	std::string EdgeInsertion();
	std::string TopCross();
	std::string Orientation();
	std::string Permutation();
	CubeGraph GetGraphicsCube();
	CubeGraph GetColourCube();
	void SetGraphicsCube(CubeGraph _cube);
	void SetColourCube(CubeGraph _cube);
	//random pattern algorithm is initiated
	bool RandomPattern();
	//returns string containing the solve algorithm(revers to get to initial scrambled state)
	std::string GetSolveAlgorithm();
	//Retuens true or false on a state
	bool StateBottomCross();
	bool StateBottomCorners();
	bool StateMiddleEdges();
	bool StateTopCross();
	bool StateTopVert();
	bool StateTopHor();
	bool StateTopLeftL();
	bool StateTopRightL();
	bool StateTopBotLeftL();
	bool StateTopBorRightL();
	bool StateTopCenter();
	bool StateOriented();
	bool StatePermuted();
	bool StateSolved();
	bool StateRow(int face, int row);
	bool StateHeadlights(int face, int row);
	std::vector<VRInput> GetSolveVRInput();
	~AI();
};