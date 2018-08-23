#pragma once
#include "stdafx.h"

//Points to x and y indicies of a 2d array
struct Face
{
	Pointer point;
	Maths calculator;
	//face colour codes (default face is green)
	int size = 9;
	int face[3][3] = {/* 0*/{ 1, 1, 1 },
		/* 1*/{ 1, 1, 1 },
		/* 2*/{ 1, 1, 1 },
	};
	Face(int faceCode);
	Face(int x0y0, int x1y0, int x2y0, int x0y1, int x1y1, int x2y1, int x0y2, int x1y2, int x2y2);
//	Face& operator=(const Face& _face);
};
//Keeps relationship array between cube center colour codes
struct CubeGraph
{
	Maths calculator;
	//center index(1d array)
	int centerIndex = 4;
	int centerWidth = 4;
	//Vector of cube faces to form cube
	std::vector<Face> cube;
	//Holds data of the center cube facing the camera
	Pointer point = calculator.From1Dto2D(centerIndex, centerWidth, point.colour);
	//Colour code
	/*Orange = 0
	  Green = 1
	  White = 2
	  Blue = 3
	  Yellow = 4
	  Red = 5
	 */                      
	 //  y
	int centerMatrix[4][4] = 
	{
		/* 0*/ {0, 2, 5, 4},
		/* 1*/ {1, 2, 3, 4},
		/* 2*/ {5, 2, 0, 4},
		/* 3*/ {3, 2, 1, 4}, };
	    //  x    0  1  2  3

//Solved Faces colour codes (Initial State)

	CubeGraph();
	CubeGraph(Face, Face, Face, Face, Face, Face);
};

//Keeps track of cube rotation, and position of pieces
class CubeTranslator
{
	Maths calculator;
	//Array of center pieces 
	CubeGraph graph;
	//The width of cube array
	//TODO: create getter and setter for this variable
public:
	//rotates face clock wise
	Face FaceCW(Face &_face);
	//rotates face anti-clockwise
	Face FaceCCW(Face &_face);
	//GetLeft Center colour code
	Pointer GetLeft(Pointer point);
	//GetRight Center colour code
	Pointer GetRight(Pointer point);
	//GetUp Center colour code
	Pointer GetUp(Pointer point);
	//GetDown Center colour code
	Pointer GetDown(Pointer point);
	void TurnUpCW(CubeGraph &_cube);
	void TurnLeftCW(CubeGraph &_cube);
	void TurnDownCW(CubeGraph &_cube);
	void TurnRightCW(CubeGraph &_cube);
	void TurnFrontCW(CubeGraph &_cube);
	void TurnBackCW(CubeGraph &_cube);
	void TurnUpCCW(CubeGraph &_cube);
	void TurnLeftCCW(CubeGraph &_cube);
	void TurnDownCCW(CubeGraph &_cube);
	void TurnRightCCW(CubeGraph &_cube);
	void TurnFrontCCW(CubeGraph &_cube);
	void TurnBackCCW(CubeGraph &_cube);
	//manipulates cube based on movelist
	Face GetFace(CubeGraph _cube, int x, int y);
};