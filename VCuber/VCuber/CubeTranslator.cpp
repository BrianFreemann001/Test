#include "stdafx.h"
#include "CubeTranslator.h"


Face CubeTranslator::FaceCW(Face &_face)
{
	Face temp = Face(0);
	temp.face[0][0] = _face.face[2][0];
	temp.face[1][0] = _face.face[2][1];
	temp.face[2][0] = _face.face[2][2];

	temp.face[0][1] = _face.face[1][0];
	temp.face[1][1] = _face.face[1][1];
	temp.face[2][1] = _face.face[1][2];

	temp.face[0][2] = _face.face[0][0];
	temp.face[1][2] = _face.face[0][1];
	temp.face[2][2] = _face.face[0][2];

	_face = temp;
	return temp;
}

Face CubeTranslator::FaceCCW(Face &_face)
{
	Face temp = Face(0);
	temp.face[0][0] = _face.face[0][2];
	temp.face[1][0] = _face.face[0][1];
	temp.face[2][0] = _face.face[0][0];

	temp.face[0][1] = _face.face[1][2];
	temp.face[1][1] = _face.face[1][1];
	temp.face[2][1] = _face.face[1][0];

	temp.face[0][2] = _face.face[2][2];
	temp.face[1][2] = _face.face[2][1];
	temp.face[2][2] = _face.face[2][0];
	_face = temp;
	return temp;
}

Pointer CubeTranslator::GetLeft(Pointer _point)
{
	Pointer left;
	if (_point.y == 0)
		_point.y = 3;
	else
		_point.y -= 1;
	left = _point;
	left.colour = graph.centerMatrix[_point.x][_point.y];
	return left;
}

Pointer CubeTranslator::GetRight(Pointer _point)
{
	Pointer right;
	if (_point.y == 3)
		_point.y = 0;
	else
		_point.y += 1;
	right = _point;
	right.colour = graph.centerMatrix[_point.x][_point.y];
	return right;
}

Pointer CubeTranslator::GetUp(Pointer _point)
{
	Pointer up;
	if (_point.x == 0)
	{
		_point.x = 3;
		_point.y = 0;
	}
	else
	{
		_point.x -= 1;
		_point.y = 0;
	}
	up = _point;
	up.colour = graph.centerMatrix[_point.x][_point.y];
	return up;
}

Pointer CubeTranslator::GetDown(Pointer _point)
{

	Pointer down;
	if (_point.x == 3)
	{
		_point.x = 0;
		_point.y = 0;
	}
	else
	{
		_point.x += 1;
		_point.y = 0;
	}
	down = _point;
	down.colour = graph.centerMatrix[_point.x][_point.y];
	return down;
}



CubeGraph::CubeGraph()
{
	point.x = 1;
	point.y = 0;
	point.colour = 1;
	Face orange = Face(0);
	Face green = Face(1);
	Face white = Face(2);
	Face blue = Face(3);
	Face yellow = Face(4);
	Face red = Face(5);

	cube.push_back(orange);
	cube.push_back(green);
	cube.push_back(white);
	cube.push_back(blue);
	cube.push_back(yellow);
	cube.push_back(red);
}

CubeGraph::CubeGraph(Face orange, Face green, Face white, Face blue, Face yellow, Face red)
{
	point.x = 1;
	point.y = 0;
	point.colour = 1;
	cube.push_back(orange);
	cube.push_back(green);
	cube.push_back(white);
	cube.push_back(blue);
	cube.push_back(yellow);
	cube.push_back(red);
}

Face::Face(int faceCode)
{
	point.colour = faceCode;
	for (int i = 0; i < size; i++)
	{
		point = calculator.From1Dto2D(i, std::sqrt(size), point.colour);
		face[point.x][point.y] = point.colour;
	}
}

Face::Face(int x0y0, int x1y0, int x2y0, int x0y1, int x1y1, int x2y1, int x0y2, int x1y2, int x2y2)
{
	int tempface[3][3] = { {x0y0, x1y0, x2y0},
	{x0y1, x1y1, x2y1},
	{x0y2, x1y2, x2y2} };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			face[j][i] = tempface[j][i];
		}
	}
}

//Face & Face::operator=(const Face & _face)
//{
//	if (!this)
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				face[j][i] = _face.face[i][j];
//			}
//		}
//		return *this;
//	}
//}

void CubeTranslator::TurnUpCW(CubeGraph & _cube)
{
	Pointer current;
	Pointer green;
	green.x = 1;
	green.y = 0;
	green.colour = 1;
	int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][0], _cube.cube[_cube.point.colour].face[0][1], _cube.cube[_cube.point.colour].face[0][2] };
	if (_cube.point.colour == 1)
		current = GetUp(_cube.point);
	else if (_cube.point.colour == 2 || _cube.point.colour == 3 || _cube.point.colour == 4)
		current = GetUp(green);
	FaceCW(_cube.cube[current.colour]);
	current = GetRight(_cube.point);
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][1] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];

	for (int i = 0; i < 2; i++)

	{

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];

		current = GetRight(current);
	}
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = tempFront[1];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[2];
}

void CubeTranslator::TurnLeftCW(CubeGraph & _cube)
{
	Pointer current;
	if (_cube.point.colour == 1)
	{
		int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][0], _cube.cube[_cube.point.colour].face[1][0], _cube.cube[_cube.point.colour].face[2][0] };
		current = GetLeft(_cube.point);
		FaceCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetUp(_cube.point);

		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][2];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][0];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnFrontCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer green;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		int tempFront[3] = { _cube.cube[green.colour].face[0][2], _cube.cube[green.colour].face[1][2], _cube.cube[green.colour].face[2][2] };
		current = GetRight(green);
		FaceCW(_cube.cube[current.colour]);
		current = GetDown(green);
		_cube.cube[green.colour].face[0][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];
		_cube.cube[green.colour].face[1][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2];
		_cube.cube[green.colour].face[2][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][0];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][2];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 4)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnBackCW(_cube);
		_cube.point = temp;
	}
}
void CubeTranslator::TurnDownCW(CubeGraph & _cube)
{
	Pointer current;
	Pointer green;
	green.x = 1;
	green.y = 0;
	green.colour = 1;
	int tempFront[3] = { _cube.cube[_cube.point.colour].face[2][0], _cube.cube[_cube.point.colour].face[2][1], _cube.cube[_cube.point.colour].face[2][2] };
	if (_cube.point.colour == 1)
		current = GetDown(_cube.point);
	else if (_cube.point.colour == 2 || _cube.point.colour == 3 || _cube.point.colour == 4)
		current = GetDown(green);
	FaceCW(_cube.cube[current.colour]);
	current = GetLeft(_cube.point);
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][1] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

	for (int i = 0; i < 2; i++)

	{

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];

		current = GetLeft(current);
	}
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = tempFront[1];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
}

void CubeTranslator::TurnRightCW(CubeGraph & _cube)
{
	Pointer current;
	if (_cube.point.colour == 1)
	{
		int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][2], _cube.cube[_cube.point.colour].face[1][2], _cube.cube[_cube.point.colour].face[2][2] };
		current = GetRight(_cube.point);
		FaceCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetDown(_cube.point);
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[1][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][0];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][2];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer green;
		Pointer left;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		current = GetLeft(green);
		left = current;
		int tempFront[3] = { _cube.cube[current.colour].face[0][0], _cube.cube[current.colour].face[1][0], _cube.cube[current.colour].face[2][0] };
		current = GetLeft(current);
		FaceCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetUp(green);

		_cube.cube[left.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];
		_cube.cube[left.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1];
		_cube.cube[left.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 3)
	{
		Pointer green;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		int tempFront[3] = { _cube.cube[green.colour].face[0][0], _cube.cube[green.colour].face[1][0], _cube.cube[green.colour].face[2][0] };
		current = GetLeft(green);
		FaceCW(_cube.cube[current.colour]);
		current = GetUp(green);

		_cube.cube[green.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
		_cube.cube[green.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0];
		_cube.cube[green.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][2];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][0];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[2];
	}
	else if (_cube.point.colour == 4)
	{
		Pointer green;
		Pointer left;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		current = GetRight(green);
		left = current;
		int tempFront[3] = { _cube.cube[current.colour].face[0][0], _cube.cube[current.colour].face[1][0], _cube.cube[current.colour].face[2][0] };
		current = GetLeft(current);
		FaceCW(_cube.cube[current.colour]);
		current = GetUp(green);

		_cube.cube[left.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];
		_cube.cube[left.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1];
		_cube.cube[left.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
	}
}

void CubeTranslator::TurnFrontCW(CubeGraph & _cube)
{
	if (_cube.point.colour == 1)
	{

		Pointer current;
		FaceCW(_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]]);
		current = GetDown(_cube.point);

		int tempFront[3] = { _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0], _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1],_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] };

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][0];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnRightCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnBackCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 4)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnLeftCW(_cube);
		_cube.point = temp;
	}
}

void CubeTranslator::TurnBackCCW(CubeGraph & _cube)
{
	if (_cube.point.colour == 1)
	{

		Pointer current;
		current = GetRight(_cube.point);
		current = GetRight(current);
		FaceCCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);

		current = GetUp(_cube.point);
		int tempFront[3] = { _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0], _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1],_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] };

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][0];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnLeftCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnFrontCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 4)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnRightCCW(_cube);
		_cube.point = temp;
	}
}

void CubeTranslator::TurnUpCCW(CubeGraph & _cube)
{
	Pointer current;
	Pointer green;
	green.x = 1;
	green.y = 0;
	green.colour = 1;
	int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][0], _cube.cube[_cube.point.colour].face[0][1], _cube.cube[_cube.point.colour].face[0][2] };
	if (_cube.point.colour == 1)
		current = GetUp(_cube.point);
	else if (_cube.point.colour == 2 || _cube.point.colour == 3 || _cube.point.colour == 4)
		current = GetUp(green);
	FaceCCW(_cube.cube[current.colour]);
	current = GetLeft(_cube.point);
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][1] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];

	for (int i = 0; i < 2; i++)

	{

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];

		current = GetLeft(current);
	}
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = tempFront[1];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[2];
}

void CubeTranslator::TurnLeftCCW(CubeGraph & _cube)
{
	Pointer current;
	if (_cube.point.colour == 1)
	{
		int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][0], _cube.cube[_cube.point.colour].face[1][0], _cube.cube[_cube.point.colour].face[2][0] };
		current = GetLeft(_cube.point);
		FaceCCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetDown(_cube.point);
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][2];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][0];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnFrontCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnRightCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 4)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnBackCCW(_cube);
		_cube.point = temp;
	}
}

void CubeTranslator::TurnDownCCW(CubeGraph & _cube)
{
	Pointer current;
	Pointer green;
	green.x = 1;
	green.y = 0;
	green.colour = 1;
	int tempFront[3] = { _cube.cube[_cube.point.colour].face[2][0], _cube.cube[_cube.point.colour].face[2][1], _cube.cube[_cube.point.colour].face[2][2] };
	if (_cube.point.colour == 1)
		current = GetDown(_cube.point);
	else if (_cube.point.colour == 2 || _cube.point.colour == 3 || _cube.point.colour == 4)
		current = GetDown(green);
	FaceCCW(_cube.cube[current.colour]);
	current = GetRight(_cube.point);
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][1] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1];
	_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

	for (int i = 0; i < 2; i++)

	{

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];

		current = GetRight(current);
	}
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = tempFront[1];
	_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
}

void CubeTranslator::TurnRightCCW(CubeGraph & _cube)
{
	Pointer current;
	if (_cube.point.colour == 1)
	{
		int tempFront[3] = { _cube.cube[_cube.point.colour].face[0][2], _cube.cube[_cube.point.colour].face[1][2], _cube.cube[_cube.point.colour].face[2][2] };
		current = GetRight(_cube.point);
		FaceCCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetUp(_cube.point);
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[0][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[1][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2];
		_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]].face[2][2] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][0];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetUp(current).x][GetUp(current).y]].face[0][2];

		current = GetUp(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer green;
		Pointer left;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		current = GetLeft(green);
		left = current;
		int tempFront[3] = { _cube.cube[current.colour].face[0][0], _cube.cube[current.colour].face[1][0], _cube.cube[current.colour].face[2][0] };
		current = GetLeft(current);
		FaceCCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);
		current = GetDown(green);
		_cube.cube[left.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];
		_cube.cube[left.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1];
		_cube.cube[left.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = tempFront[0];
	}
	else if (_cube.point.colour == 3)
	{
		Pointer green;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		int tempFront[3] = { _cube.cube[green.colour].face[0][0], _cube.cube[green.colour].face[1][0], _cube.cube[green.colour].face[2][0] };
		current = GetLeft(green);
		FaceCCW(_cube.cube[current.colour]);
		current = GetDown(green);
		_cube.cube[green.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];
		_cube.cube[green.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0];
		_cube.cube[green.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][2];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[2][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetDown(current).x][GetDown(current).y]].face[0][0];

		current = GetDown(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[2];
	}
	else if (_cube.point.colour == 4)
	{
		Pointer green;
		Pointer left;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		current = GetRight(green);
		left = current;
		int tempFront[3] = { _cube.cube[current.colour].face[0][0], _cube.cube[current.colour].face[1][0], _cube.cube[current.colour].face[2][0] };
		current = GetLeft(current);
		FaceCCW(_cube.cube[current.colour]);
		current = GetDown(green);
		_cube.cube[left.colour].face[0][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2];
		_cube.cube[left.colour].face[1][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1];
		_cube.cube[left.colour].face[2][0] = _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0];

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = tempFront[2];
	}
}

void CubeTranslator::TurnFrontCCW(CubeGraph & _cube)
{
	if (_cube.point.colour == 1)
	{
		Pointer current;
		FaceCCW(_cube.cube[_cube.centerMatrix[_cube.point.x][_cube.point.y]]);
		current = GetDown(_cube.point);
		int tempFront[3] = { _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0], _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1],_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] };

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetLeft(current).x][GetLeft(current).y]].face[2][0];

		current = GetLeft(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer green;
		Pointer temp;
		green.x = 1;
		green.y = 0;
		green.colour = 1;
		temp = _cube.point;
		_cube.point = green;
		TurnRightCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnBackCCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 4)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnLeftCCW(_cube);
		_cube.point = temp;
	}
}

void CubeTranslator::TurnBackCW(CubeGraph & _cube)
{
	if (_cube.point.colour)
	{

		Pointer current;
		current = GetRight(_cube.point);
		current = GetRight(current);
		FaceCW(_cube.cube[_cube.centerMatrix[current.x][current.y]]);

		current = GetUp(_cube.point);
		int tempFront[3] = { _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0], _cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1],_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] };

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[0][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][1] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[1][0];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][2] = _cube.cube[_cube.centerMatrix[GetRight(current).x][GetRight(current).y]].face[2][0];

		current = GetRight(current);

		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[0][0] = tempFront[2];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[1][0] = tempFront[1];
		_cube.cube[_cube.centerMatrix[current.x][current.y]].face[2][0] = tempFront[0];
	}
	else if (_cube.point.colour == 2)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnLeftCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 3)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnFrontCW(_cube);
		_cube.point = temp;
	}
	else if (_cube.point.colour == 4)
	{
		Pointer temp;
		temp = _cube.point;
		_cube.point.x = 1;
		_cube.point.y = 0;
		_cube.point.colour = 1;
		TurnRightCW(_cube);
		_cube.point = temp;
	}
}

Face CubeTranslator::GetFace(CubeGraph _cube, int x, int y)
{
	Face _face = _cube.cube[_cube.centerMatrix[x][y]];
	_face.point.x = x;
	_face.point.y = y;
	_face.point.colour = _cube.centerMatrix[x][y];
	return  _face;
}
