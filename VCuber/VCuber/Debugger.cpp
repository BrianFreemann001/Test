#include "stdafx.h"
#include "Debugger.h"


void CubeDebugger::Keys()
{
	printf("\n\t\t\t\t\t\t %s", "Key");
	printf("\n\t\t\t\t\t\t %s", "Orange - 0");
	printf("\n\t\t\t\t\t\t %s", "Green - 1");
	printf("\n\t\t\t\t\t\t %s", "White - 2");
	printf("\n\t\t\t\t\t\t %s", "Blue - 3");
	printf("\n\t\t\t\t\t\t %s", "Yellow - 4");
	printf("\n\t\t\t\t\t\t %s \n\n", "Red - 5");
}

void CubeDebugger::ShowCenterList(CubeGraph _cube)
{
	//Prints a 4x4 matrix of the list of centers
	//if using 2d to 1d calculator, pass in x as y, and y as x 2dto1d[y][x]
	printf("\n%s", "Center Matrix");
	printf("\n %i", _cube.centerMatrix[0][0]); printf("%c", ','); printf(" %i", _cube.centerMatrix[0][1]); printf("%c", ','); printf(" %i", _cube.centerMatrix[0][2]); printf("%c", ','); printf(" %i", _cube.centerMatrix[0][3]); printf("%c", ',');
	printf("\n %i", _cube.centerMatrix[1][0]); printf("%c", ','); printf(" %i", _cube.centerMatrix[1][1]); printf("%c", ','); printf(" %i", _cube.centerMatrix[1][2]); printf("%c", ','); printf(" %i", _cube.centerMatrix[1][3]); printf("%c", ',');
	printf("\n %i", _cube.centerMatrix[2][0]); printf("%c", ','); printf(" %i", _cube.centerMatrix[2][1]); printf("%c", ','); printf(" %i", _cube.centerMatrix[2][2]); printf("%c", ','); printf(" %i", _cube.centerMatrix[2][3]); printf("%c", ',');
	printf("\n %i", _cube.centerMatrix[3][0]); printf("%c", ','); printf(" %i", _cube.centerMatrix[3][1]); printf("%c", ','); printf(" %i", _cube.centerMatrix[3][2]); printf("%c", ','); printf(" %i", _cube.centerMatrix[3][3]); printf("%c\n\n", ',');
}

void CubeDebugger::ShowFaces(CubeGraph _cube, std::string name)
{
	printf("\n%s", name.c_str());
	printf("\n %i", _cube.cube[0].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[0][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[0].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[1][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[0].face[2][0]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[2][2]);  printf("%c", ',');

	printf("\n\n %i", _cube.cube[1].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[0][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[0][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[0][0]); printf("%c", ','); printf(" %i", _cube.cube[3].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[0][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[0][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[1].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[1][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[1][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[1][0]); printf("%c", ','); printf(" %i", _cube.cube[3].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[1][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[1][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[1].face[2][0]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[2][0]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[2][0]); printf("%c", ','); printf(" %i", _cube.cube[3].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[2][0]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[2][2]);  printf("%c", ',');

	printf("\n\n %i", _cube.cube[5].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[0][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[5].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[1][2]);  printf("%c", ',');
	printf("\n %i", _cube.cube[5].face[2][0]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[2][1]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[2][2]);  printf("%c\n\n", ',');
}

//void CubeDebugger::ShowFaces(CubeGraph _cube)
//{
//	printf("\n%s", "Faces");
//	printf("\n %i", _cube.cube[0].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[2][0]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[0].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[2][1]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[0].face[0][2]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[0].face[2][2]);  printf("%c", ',');
//
//	printf("\n\n %i", _cube.cube[1].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[2][0]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[2][0]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[0][0]); printf("%c", ','); printf(" %i", _cube.cube[3].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[2][0]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[2][0]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[1].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[2][1]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[2][1]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[0][1]); printf("%c", ','); printf(" %i", _cube.cube[3].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[2][1]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[2][1]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[1].face[0][2]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[1].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[2].face[0][2]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[2].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[3].face[0][2]); printf("%c", ','); printf(" %i", _cube.cube[3].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[3].face[2][2]);  printf("%c", ',');	 printf("\t %i", _cube.cube[4].face[0][2]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[4].face[2][2]);  printf("%c", ',');
//
//	printf("\n\n %i", _cube.cube[5].face[0][0]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[1][0]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[2][0]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[5].face[0][1]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[1][1]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[2][1]);  printf("%c", ',');
//	printf("\n %i", _cube.cube[5].face[0][2]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[1][2]);  printf("%c", ','); printf(" %i", _cube.cube[5].face[2][2]);  printf("%c\n\n", ',');
//}
