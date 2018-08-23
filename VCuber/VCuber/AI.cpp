#include "stdafx.h"
#include "AI.h"

AI::AI()
{
	botCubeG = CubeGraph();
	resetFace.x = 1;
	resetFace.y = 0;
	resetFace.colour = 1;
	notSolved.append("Cube not solved");
}

AI::AI(CubeGraph _cube, CubeGraph _colourCube, CubeGraph _solvedGraphicsCube)
{
	botCubeG = _cube;
	botCubeC = _colourCube;
	solvedCubeG = _solvedGraphicsCube;
	solvedCubeC = CubeGraph(Face(0), Face(1), Face(2), Face(3), Face(4), Face(5));
	resetFace.x = 1;
	resetFace.y = 0;
	resetFace.colour = 1;
	notSolved.append("Cube not solved");
}

int AI::Evaluate()
{
	if (StateSolved())
		return 0;
	if (StateOriented() && StateTopCross() && StateMiddleEdges() && StateBottomCorners() && StateBottomCross())
		return 5;
	if (StateTopCross() && StateMiddleEdges() && StateBottomCorners() && StateBottomCross())
		return 4;
	if (StateMiddleEdges() && StateBottomCorners() && StateBottomCross())
		return 3;
	if (StateBottomCorners() && StateBottomCross())
		return 2;
	if (StateBottomCross())
		return 1;
	else
		return 6;
}

bool AI::Solve(int state)
{
	fullMovelist.clear();
	movelist.clear();
	if (Evaluate() == 0)
		return true;
	if (Evaluate() == 5)
	{
		fullMovelist.append(Permutation());
		return true;
	}
	if (Evaluate() == 4)
	{
		fullMovelist.append(Orientation());
		fullMovelist.append(Permutation());
		return true;
	}
	if (Evaluate() == 3)
	{
		fullMovelist.append(TopCross());
		fullMovelist.append(Orientation());
		fullMovelist.append(Permutation());
		return true;
	}
	if (Evaluate() == 2)
	{
		fullMovelist.append(EdgeInsertion());
		fullMovelist.append(TopCross());
		fullMovelist.append(Orientation());
		fullMovelist.append(Permutation());
		return true;
	}
	if (Evaluate() == 1)
	{
		fullMovelist.append(BottomCorners());
		fullMovelist.append(EdgeInsertion());
		fullMovelist.append(TopCross());
		fullMovelist.append(Orientation());
		fullMovelist.append(Permutation());
		return true;
	}
	if (Evaluate() == 6)
	{
		fullMovelist.append(BottomCross());
		fullMovelist.append(BottomCorners());
		fullMovelist.append(EdgeInsertion());
		fullMovelist.append(TopCross());
		fullMovelist.append(Orientation());
		fullMovelist.append(Permutation());
		return true;
	}
	else
		return false;
}

bool AI::Scramble()
{
	//Under Construction
	return false;
}

bool AI::Scramble(std::string _scrambleAlg)
{
	//Under Construction                                                                                                                                                                                                                                                                                                                                                                
	return false;
}

std::string AI::BottomCross()
{
	std::string result;
	int u, v;
	unsigned int current = 1;
	while (!StateBottomCross())
	{
		botCubeC.point = resetFace;
		botCubeG.point = resetFace;
		result.append("-,");
		for (int i = 1; i < 5; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				//if (!(botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, i).x][botCubeG.calculator.From1Dto2D(j, 3, i).y] == solvedCubeG.cube[current].face[0][1]))
				//{
				//}
				if ((botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, i).x][botCubeG.calculator.From1Dto2D(j, 3, i).y] == solvedCubeG.cube[current].face[2][1]))
				{
					u = botCubeG.calculator.From1Dto2D(j, 3, i).x;
					v = botCubeG.calculator.From1Dto2D(j, 3, i).y;
					if (botCubeC.cube[i].face[1][1] != botCubeC.cube[current].face[1][1])
					{
						if (u == 0 && v == 1)
						{
							while (botCubeC.point.colour != botCubeC.cube[current].face[1][1])
							{
								botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
								botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
								result.append(">,");
							}
							while (botCubeG.cube[current].face[0][1] != solvedCubeG.cube[current].face[2][1])
							{
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								result.append("U,");
							}
						}
						else if (u == 1 && v == 0)
						{
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnFrontCCW(botCubeC);
							cubeTranslator.TurnFrontCCW(botCubeG);
							result.append("F,U,F1,");
							while (botCubeC.point.colour != botCubeC.cube[current].face[1][1])
							{
								botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
								botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
								result.append(">,");
							}
							while (botCubeG.cube[current].face[0][1] != solvedCubeG.cube[current].face[2][1])
							{
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								result.append("U,");
							}
						}
						else if (u == 1 && v == 2)
						{
							cubeTranslator.TurnFrontCCW(botCubeC);
							cubeTranslator.TurnFrontCCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							result.append("F1,U,F,");
							while (botCubeC.point.colour != botCubeC.cube[current].face[1][1])
							{
								botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
								botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
								result.append(">,");
							}
							while (botCubeG.cube[current].face[0][1] != solvedCubeG.cube[current].face[2][1])
							{
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								result.append("U,");
							}
						}
						else if (u == 2 && v == 1)
						{
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							result.append("F,F,U,");
							while (botCubeC.point.colour != botCubeC.cube[current].face[1][1])
							{
								botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
								botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
								result.append(">,");
							}
							while (botCubeG.cube[current].face[0][1] != solvedCubeG.cube[current].face[2][1])
							{
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								result.append("U,");
							}
						}
					}
					else if (botCubeC.cube[i].face[1][1] == botCubeC.cube[current].face[1][1])
					{
						if (u == 1 && v == 0)
						{
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							result.append("F,");
						}
						else if (u == 1 && v == 2)
						{
							cubeTranslator.TurnFrontCCW(botCubeC);
							cubeTranslator.TurnFrontCCW(botCubeG);
							result.append("F1,");
						}
						else if (u == 2 && v == 1)
						{
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							cubeTranslator.TurnFrontCW(botCubeC);
							cubeTranslator.TurnFrontCW(botCubeG);
							result.append("F,F,");
						}
					}
				}
				if (botCubeG.cube[current].face[0][1] == solvedCubeG.cube[current].face[2][1])
				{
					if ((botCubeC.cube[current].face[1][1] != botCubeC.cube[current].face[0][1]))
					{
						cubeTranslator.TurnFrontCW(botCubeC);
						cubeTranslator.TurnFrontCW(botCubeG);
						cubeTranslator.TurnRightCW(botCubeC);
						cubeTranslator.TurnRightCW(botCubeG);
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						cubeTranslator.TurnRightCCW(botCubeC);
						cubeTranslator.TurnRightCCW(botCubeG);
						cubeTranslator.TurnUpCCW(botCubeC);
						cubeTranslator.TurnUpCCW(botCubeG);
						cubeTranslator.TurnFrontCCW(botCubeC);
						cubeTranslator.TurnFrontCCW(botCubeG);
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						result.append("F,R,U,R1,U1,F1,U,");
					}
				}
				if ((botCubeC.cube[current].face[1][1] == botCubeC.cube[current].face[0][1]) && botCubeG.cube[current].face[0][1] == solvedCubeG.cube[current].face[2][1])
				{
					cubeTranslator.TurnFrontCW(botCubeC);
					cubeTranslator.TurnFrontCW(botCubeG);
					cubeTranslator.TurnFrontCW(botCubeC);
					cubeTranslator.TurnFrontCW(botCubeG);
					result.append("F,F,");
					break;
				}
			}
			botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
			botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
			result.append(">,");
			if (botCubeC.cube[current].face[2][1] == solvedCubeC.cube[current].face[2][1])
			{

				//	botCubeC.point = resetFace;
				//	botCubeG.point = resetFace;
				//	result.append("-,");
				//for (int i = 0; i < current; i++)
				//{
				//	botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
				//	botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
				//	result.append(">,");
				//}
				break;
			}
		}
		current += 1;
		if (current > 4)
			current = 1;
#pragma region delete
		//if (!g)
		//{
		//	//step1
		//	for (int i = 0; i < 6; i++)
		//	{
		//		for (int j = 0; j < 9; j++)
		//		{
		//			u = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x;
		//			v = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y;
		//			if (botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x][botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y] == solvedCubeG.cube[1].face[2][1])
		//			{
		//				if (botCubeC.cube[i].face[1][1] == GREEN && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("F,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						result.append("F1,");
		//						g = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == WHITE && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U,F,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						result.append("R,D1,");
		//						g = true;
		//						break;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						result.append("D1,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						result.append("R1,D1,");
		//						g = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == BLUE && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U,U,F,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("B,D,D,");
		//						g = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("D,D,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("B1,D,D,");
		//						g = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == YELLOW && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U1,F,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("L,D,");
		//						g = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("D,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("L1,D,");
		//						g = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == YELLOW && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U,R1,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("R1,F,");
		//						g = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U1,R1,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("L,F,");
		//						g = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == RED && botCubeC.cube[i].face[u][v] == GREEN)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("D.R,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("R,F,");
		//						g = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("D1,R,F,");
		//						g = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("L1,F,");
		//						g = true;
		//					}
		//				}
		//				if (g)
		//					break;
		//			}
		//		}
		//		if (g)
		//			break;
		//	}
		//}

		////Step 2
		//if (!w)
		//{

		//	for (int i = 0; i < 6; i++)
		//	{
		//		for (int j = 0; j < 9; j++)
		//		{
		//			u = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x;
		//			v = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y;
		//			if (botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x][botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y] == solvedCubeG.cube[2].face[2][1])
		//			{
		//				if (botCubeC.cube[i].face[1][1] == GREEN && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("U1,R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						result.append("F,R,F1,R1,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("F,U1,F1,R,R,");
		//						w = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == WHITE && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						result.append("R1,");
		//						w = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == BLUE && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("B1,U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("B,B,U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("B,U,R,R,");
		//						w = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == YELLOW && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("U,U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("L1,U,U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("L,L,U,U,R,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("L,U,U,R,R,");
		//						w = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == ORANGE && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("B1,R,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("U1,B1,R,");
		//						w = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						result.append("F,R1,F1,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						result.append("U,B1,R,");
		//						w = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == RED && botCubeC.cube[i].face[u][v] == WHITE)
		//				{
		//					if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("R,D1,F,D,");
		//						w = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						result.append("F,D1,F1,");
		//						w = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						result.append("F,D,D,F1,");
		//						w = true;
		//					}
		//				}
		//				if (w)
		//					break;
		//			}

		//		}
		//		if (w)
		//			break;
		//	}
		//}
		//if (!b)
		//{

		//	//Step 3
		//	for (int i = 0; i < 6; i++)
		//	{
		//		for (int j = 0; j < 9; j++)
		//		{
		//			u = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x;
		//			v = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y;
		//			if (botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x][botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y] == solvedCubeG.cube[3].face[2][1])
		//			{
		//				if (botCubeC.cube[i].face[1][1] == GREEN && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U,U,B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("F1,U,U,B,B,F,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("F,U,U,B,B,F,");
		//						b = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == WHITE && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U1,B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("R1,U1,R,B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("R,U1,R,B,B,");
		//						b = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == BLUE && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						result.append("B1,");
		//						b = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == YELLOW && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U,B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("L1,U,B,B,");
		//						b = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("L,L,U,B,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("L,U,B,B,");
		//						b = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == ORANGE && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U1,L1,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U,U,L1,B,");
		//						b = true;
		//					}
		//					else if (u == 2 && v == 1)\
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("U,L1,B,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("L1,B,");
		//						b = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == RED && botCubeC.cube[i].face[u][v] == BLUE)
		//				{
		//					if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						result.append("D1,R1,D,B1,");
		//						b = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnDownCCW(botCubeC);
		//						cubeTranslator.TurnDownCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						result.append("D1,B1,D,B,");
		//						b = true;
		//					}
		//				}
		//			}
		//			if (b)
		//				break;
		//		}
		//		if (b)
		//			break;
		//	}
		//}
		//if (!y)
		//{
		//	//Step 4
		//	for (int i = 0; i < 6; i++)
		//	{
		//		for (int j = 0; j < 9; j++)
		//		{
		//			u = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x;
		//			v = botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y;
		//			if (botCubeG.cube[i].face[botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).x][botCubeG.calculator.From1Dto2D(j, 3, botCubeC.cube[i].face[1][1]).y] == solvedCubeG.cube[4].face[2][1])
		//			{
		//				if (botCubeC.cube[i].face[1][1] == GREEN && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("U,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("F1,U,F,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("F,U,F1,L,L,");
		//						y = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == WHITE && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("U,U,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("R1,U,U,R,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnRightCW(botCubeC);
		//						cubeTranslator.TurnRightCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnUpCW(botCubeC);
		//						cubeTranslator.TurnUpCW(botCubeG);
		//						cubeTranslator.TurnRightCCW(botCubeC);
		//						cubeTranslator.TurnRightCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("R,U,U,R1,L,L,");
		//						y = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == BLUE && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("U1,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("B1,U1,B,L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("B,U1,B1,L,L,");
		//						y = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == YELLOW && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("L,L,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						result.append("L,");
		//						y = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						result.append("L1,");
		//						y = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == ORANGE && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 0 && v == 1)
		//					{
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						result.append("B,L1,B1,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 2)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnBackCW(botCubeC);
		//						cubeTranslator.TurnBackCW(botCubeG);
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnBackCCW(botCubeC);
		//						cubeTranslator.TurnBackCCW(botCubeG);
		//						result.append("U1,B,L1,B1,");
		//						y = true;
		//					}
		//					else if (u == 2 && v == 1)
		//					{
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("F1,L,F,");
		//						y = true;
		//					}
		//					else if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnUpCCW(botCubeC);
		//						cubeTranslator.TurnUpCCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnLeftCW(botCubeC);
		//						cubeTranslator.TurnLeftCW(botCubeG);
		//						cubeTranslator.TurnFrontCW(botCubeC);
		//						cubeTranslator.TurnFrontCW(botCubeG);
		//						result.append("U1,F1,L,F,");
		//						y = true;
		//					}
		//				}
		//				else if (botCubeC.cube[i].face[1][1] == RED && botCubeC.cube[i].face[u][v] == YELLOW)
		//				{
		//					if (u == 1 && v == 0)
		//					{
		//						cubeTranslator.TurnLeftCCW(botCubeC);
		//						cubeTranslator.TurnLeftCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						cubeTranslator.TurnFrontCCW(botCubeC);
		//						cubeTranslator.TurnFrontCCW(botCubeG);
		//						cubeTranslator.TurnDownCW(botCubeC);
		//						cubeTranslator.TurnDownCW(botCubeG);
		//						result.append("L1,D,F1,D,");
		//						y = true;
		//					}
		//				}
		//				if (y)
		//					break;
		//			}

		//		}
		//		if (y)
		//			break;
		//	}
		//}
#pragma endregion

	}
	botCubeC.point = resetFace;
	botCubeG.point = resetFace;
	result.append("-,");
	return result;
}

std::string AI::F2L()
{
	std::string result;
	result.append(BottomCorners());
	result.append(EdgeInsertion());
	return result;
}

std::string AI::BottomCorners()
{
	bool g = false;
	bool w = false;
	bool b = false;
	bool y = false;
	std::string result;
	unsigned int current = 1;
	while (current < 5)
	{
		solvedCubeC.point = botCubeC.point;
		solvedCubeG.point = botCubeG.point;

		for (int i = 0; i < 5; i++)
		{
			if (!(botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2]))
			{
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCCW(botCubeC);
				cubeTranslator.TurnRightCCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				result.append("R,U,R1,U,");
			}
			if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && !(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
			{
				while (!(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
				{
					cubeTranslator.TurnRightCW(botCubeC);
					cubeTranslator.TurnRightCW(botCubeG);
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					cubeTranslator.TurnRightCCW(botCubeC);
					cubeTranslator.TurnRightCCW(botCubeG);
					cubeTranslator.TurnUpCCW(botCubeC);
					cubeTranslator.TurnUpCCW(botCubeG);
					cubeTranslator.TurnRightCW(botCubeC);
					cubeTranslator.TurnRightCW(botCubeG);
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					cubeTranslator.TurnRightCCW(botCubeC);
					cubeTranslator.TurnRightCCW(botCubeG);
					result.append("R,U,R1,U1,R,U,R1,");
				}
			}
			if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && (botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
			{
				if (current == 1)
				{
					g = true;
					break;
				}
				else if (current == 2)
				{
					w = true;
					break;
				}
				else if (current == 3)
				{
					b = true;
					break;
				}
				else if (current == 4)
				{
					y = true;
					break;
				}
			}
		}
		current += 1;
		botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
		botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
		result.append(">,");
		if (current == 5)
		{
			while (!g || !w || !b || !y)
			{
				botCubeC.point = resetFace;
				botCubeG.point = resetFace;
				result.append("-,");
				if (!g)
				{
					current = 1;
					for (int i = 0; i < 5; i++)
					{
						if (!(botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2]))
						{
							cubeTranslator.TurnRightCW(botCubeC);
							cubeTranslator.TurnRightCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnRightCCW(botCubeC);
							cubeTranslator.TurnRightCCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							result.append("R,U,R1,U,");
						}
						if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && (botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							g = true;
							break;
						}
						else if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && !(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							while (!((botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2])))
							{
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								cubeTranslator.TurnUpCCW(botCubeC);
								cubeTranslator.TurnUpCCW(botCubeG);
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								result.append("R,U,R1,U1,R,U,R1,");
							}
						}
					}
				}
				if (!w)
				{
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					current = 2;
					for (int i = 0; i < 5; i++)
					{
						if (!(botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2]))
						{
							cubeTranslator.TurnRightCW(botCubeC);
							cubeTranslator.TurnRightCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnRightCCW(botCubeC);
							cubeTranslator.TurnRightCCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							result.append("R,U,R1,U,");
						}
						if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && (botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							w = true;
							break;
						}
						else if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && !(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							while (!((botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2])))
							{
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								cubeTranslator.TurnUpCCW(botCubeC);
								cubeTranslator.TurnUpCCW(botCubeG);
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								result.append("R,U,R1,U1,R,U,R1,");
							}
						}
					}
				}
				if (!b)
				{
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					current = 3;
					for (int i = 0; i < 5; i++)
					{
						if (!(botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2]))
						{
							cubeTranslator.TurnRightCW(botCubeC);
							cubeTranslator.TurnRightCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnRightCCW(botCubeC);
							cubeTranslator.TurnRightCCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							result.append("R,U,R1,U,");
						}
						if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && (botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							b = true;
							break;
						}
						else if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && !(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							while (!((botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2])))
							{
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								cubeTranslator.TurnUpCCW(botCubeC);
								cubeTranslator.TurnUpCCW(botCubeG);
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								result.append("R,U,R1,U1,R,U,R1,");
							}
						}
					}
				}
				if (!y)
				{
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
					botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
					result.append(">,");
					current = 4;
					for (int i = 0; i < 5; i++)
					{
						if (!(botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2]))
						{
							cubeTranslator.TurnRightCW(botCubeC);
							cubeTranslator.TurnRightCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							cubeTranslator.TurnRightCCW(botCubeC);
							cubeTranslator.TurnRightCCW(botCubeG);
							cubeTranslator.TurnUpCW(botCubeC);
							cubeTranslator.TurnUpCW(botCubeG);
							result.append("R,U,R1,U,");
						}
						if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && (botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							y = true;
							break;
						}
						else if (botCubeG.cube[current].face[2][2] == solvedCubeG.cube[current].face[2][2] && !(botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2]))
						{
							while (!((botCubeC.cube[current].face[2][2] == solvedCubeC.cube[current].face[2][2])))
							{
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								cubeTranslator.TurnUpCCW(botCubeC);
								cubeTranslator.TurnUpCCW(botCubeG);
								cubeTranslator.TurnRightCW(botCubeC);
								cubeTranslator.TurnRightCW(botCubeG);
								cubeTranslator.TurnUpCW(botCubeC);
								cubeTranslator.TurnUpCW(botCubeG);
								cubeTranslator.TurnRightCCW(botCubeC);
								cubeTranslator.TurnRightCCW(botCubeG);
								result.append("R,U,R1,U1,R,U,R1,");
							}
						}
					}
				}
			}
			current = 5;
		}
	}
	botCubeC.point = resetFace;
	botCubeG.point = resetFace;
	result.append("-,");
	return result;
}

std::string AI::EdgeInsertion()
{
	std::string result;
	bool g = false;
	bool w = false;
	bool b = false;
	bool y = false;
	int counter = 0;
	int i = 1;
	while (!StateMiddleEdges())
	{
		while (counter < 4 && !(g && w && b && y))
		{
			if ((botCubeG.cube[i].face[0][1] == solvedCubeG.cube[i].face[1][2]) || botCubeG.cube[i].face[0][1] == solvedCubeG.cube[i].face[1][0])
			{
				if (!(botCubeC.cube[i].face[1][1] == botCubeC.cube[i].face[0][1]))
				{
					cubeTranslator.TurnFrontCW(botCubeC);
					cubeTranslator.TurnFrontCW(botCubeG);
					cubeTranslator.TurnRightCW(botCubeC);
					cubeTranslator.TurnRightCW(botCubeG);
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					cubeTranslator.TurnRightCCW(botCubeC);
					cubeTranslator.TurnRightCCW(botCubeG);
					cubeTranslator.TurnUpCCW(botCubeC);
					cubeTranslator.TurnUpCCW(botCubeG);
					cubeTranslator.TurnFrontCCW(botCubeC);
					cubeTranslator.TurnFrontCCW(botCubeG);
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					result.append("F,R,U,R1,U1,F1,U,");
				}
				if (botCubeC.cube[i].face[1][1] == botCubeC.cube[i].face[0][1])
				{
					if (botCubeG.cube[i].face[0][1] == solvedCubeG.cube[i].face[1][2])
					{
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						cubeTranslator.TurnRightCW(botCubeC);
						cubeTranslator.TurnRightCW(botCubeG);
						cubeTranslator.TurnUpCCW(botCubeC);
						cubeTranslator.TurnUpCCW(botCubeG);
						cubeTranslator.TurnRightCCW(botCubeC);
						cubeTranslator.TurnRightCCW(botCubeG);
						cubeTranslator.TurnUpCCW(botCubeC);
						cubeTranslator.TurnUpCCW(botCubeG);
						cubeTranslator.TurnFrontCCW(botCubeC);
						cubeTranslator.TurnFrontCCW(botCubeG);
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						cubeTranslator.TurnFrontCW(botCubeC);
						cubeTranslator.TurnFrontCW(botCubeG);
						result.append("U,R,U1,R1,U1,F1,U,F,");
						if (i == 1)
							g = true;
						else if (i == 2)
							w = true;
						else if (i == 3)
							b = true;
						else if (i == 4)
							y = true;
						counter = 4;
					}
					if (botCubeG.cube[i].face[0][1] == solvedCubeG.cube[i].face[1][0])
					{
						cubeTranslator.TurnUpCCW(botCubeC);
						cubeTranslator.TurnUpCCW(botCubeG);
						cubeTranslator.TurnLeftCCW(botCubeC);
						cubeTranslator.TurnLeftCCW(botCubeG);
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						cubeTranslator.TurnLeftCW(botCubeC);
						cubeTranslator.TurnLeftCW(botCubeG);
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						cubeTranslator.TurnFrontCW(botCubeC);
						cubeTranslator.TurnFrontCW(botCubeG);
						cubeTranslator.TurnUpCCW(botCubeC);
						cubeTranslator.TurnUpCCW(botCubeG);
						cubeTranslator.TurnFrontCCW(botCubeC);
						cubeTranslator.TurnFrontCCW(botCubeG);
						result.append("U1,L1,U,L,U,F,U1,F1,");
						if (i == 1)
							y = true;
						else if (i == 2)
							g = true;
						else if (i == 3)
							w = true;
						else if (i == 4)
							b = true;
						counter = 4;
					}
				}

			}
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			result.append("U,");
			counter += 1;
			if (counter == 4)
			{
				if (!(botCubeC.cube[i].face[1][1] == botCubeC.cube[i].face[1][2]) || !((botCubeG.cube[i].face[1][2] == solvedCubeG.cube[i].face[1][2])))
				{
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					cubeTranslator.TurnRightCW(botCubeC);
					cubeTranslator.TurnRightCW(botCubeG);
					cubeTranslator.TurnUpCCW(botCubeC);
					cubeTranslator.TurnUpCCW(botCubeG);
					cubeTranslator.TurnRightCCW(botCubeC);
					cubeTranslator.TurnRightCCW(botCubeG);
					cubeTranslator.TurnUpCCW(botCubeC);
					cubeTranslator.TurnUpCCW(botCubeG);
					cubeTranslator.TurnFrontCCW(botCubeC);
					cubeTranslator.TurnFrontCCW(botCubeG);
					cubeTranslator.TurnUpCW(botCubeC);
					cubeTranslator.TurnUpCW(botCubeG);
					cubeTranslator.TurnFrontCW(botCubeC);
					cubeTranslator.TurnFrontCW(botCubeG);
					result.append("U,R,U1,R1,U1,F1,U,F,");
				}
			}
		}
		botCubeC.point = cubeTranslator.GetRight(botCubeC.point);
		botCubeG.point = cubeTranslator.GetRight(botCubeG.point);
		result.append(">,");
		i += 1;

		if (i == 1 && g)
		{
			i += 1;
		}
		if (i == 2 && w)
		{
			i += 1;
		}
		if (i == 3 && b)
		{
			i += 1;
		}
		if (i == 4 && y)
		{
			i += 1;
		}
		if (i > 4)
			i = 1;
		counter = 0;
	}
	botCubeC.point = resetFace;
	botCubeG.point = resetFace;
	result.append("-,");
	return result;
}

std::string AI::TopCross()
{
	std::string result;
	while (!(StateTopCross()))
	{
		if (StateTopVert())
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("U,F,R,U,R1,U1,F1,");
		}
		else if (StateTopHor())
		{
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("F,R,U,R1,U1,F1,");
		}
		else if (StateTopLeftL())
		{
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("F,R,U,R1,U1,R,U,R1,U1,F1,");
		}
		else if (StateTopRightL())
		{
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("U1,F,R,U,R1,U1,R,U,R1,U1,F1,");
		}
		else if (StateTopBotLeftL())
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("U,F,R,U,R1,U1,R,U,R1,U1,F1,");
		}
		else if (StateTopBorRightL())
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("U,U,F,R,U,R1,U1,R,U,R1,U1,F1,");
		}
		else if (StateTopCenter())
		{
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			result.append("F,R,U,R1,U1,F1,");
		}
	}
	botCubeC.point = resetFace;
	botCubeG.point = resetFace;
	result.append("-,");
	return result;
}

std::string AI::Orientation()
{
	std::string result;
	while (!(StateOriented()))
	{
		cubeTranslator.TurnRightCCW(botCubeC);
		cubeTranslator.TurnRightCCW(botCubeG);
		cubeTranslator.TurnDownCCW(botCubeC);
		cubeTranslator.TurnDownCCW(botCubeG);
		cubeTranslator.TurnRightCW(botCubeC);
		cubeTranslator.TurnRightCW(botCubeG);
		cubeTranslator.TurnDownCW(botCubeC);
		cubeTranslator.TurnDownCW(botCubeG);
		result.append("R1,D1,R,D,");
		if (botCubeC.cube[0].face[2][2] == solvedCubeC.cube[0].face[2][2])
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			result.append("U,");
		}
	}
	return result;
}

std::string AI::Permutation()
{
	std::string result;
	bool frontH = false;
	bool rightH = false;
	bool backH = false;
	bool leftH = false;
	bool frontR = false;
	bool rightR = false;
	bool backR = false;
	bool leftR = false;
	while (!StateSolved())
	{
		frontH = StateHeadlights(GREEN, 0);
		rightH = StateHeadlights(WHITE, 0);
		backH = StateHeadlights(BLUE, 0);
		leftH = StateHeadlights(YELLOW, 0);
		frontR = StateRow(GREEN, 0);
		rightR = StateRow(WHITE, 0);
		backR = StateRow(BLUE, 0);
		leftR = StateRow(YELLOW, 0);

		if (frontR && rightR && backR && leftR)
		{
			while (!StateSolved())
			{
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				result.append("U,");
			}
		}
		else if (frontH && rightH && backH && leftH)
		{
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");
		}
		else if (frontH && !rightH && !rightR)
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U,U,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (rightH && !backH && !backR)
		{
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U1,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (backH && !leftH && !leftR)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (leftH && !frontH && !frontR)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (frontR && rightH)
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			result.append("U,U,");
			while (!StateSolved())
			{

				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCCW(botCubeC);
				cubeTranslator.TurnRightCCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");

				frontH = StateHeadlights(GREEN, 0);
				rightH = StateHeadlights(WHITE, 0);
				backH = StateHeadlights(BLUE, 0);
				leftH = StateHeadlights(YELLOW, 0);
				frontR = StateRow(GREEN, 0);
				rightR = StateRow(WHITE, 0);
				backR = StateRow(BLUE, 0);
				leftR = StateRow(YELLOW, 0);
				if (frontR && rightR && backR && leftR)
				{
					while (!StateSolved())
					{
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						result.append("U,");
					}
				}
			}
		}
		else if (rightR && backH)
		{
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			result.append("U1,");
			while (!StateSolved())
			{

				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCCW(botCubeC);
				cubeTranslator.TurnRightCCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");

				frontH = StateHeadlights(GREEN, 0);
				rightH = StateHeadlights(WHITE, 0);
				backH = StateHeadlights(BLUE, 0);
				leftH = StateHeadlights(YELLOW, 0);
				frontR = StateRow(GREEN, 0);
				rightR = StateRow(WHITE, 0);
				backR = StateRow(BLUE, 0);
				leftR = StateRow(YELLOW, 0);
				if (frontR && rightR && backR && leftR)
				{
					while (!StateSolved())
					{
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						result.append("U,");
					}
				}
			}
		}
		else if (backR && leftH)
		{
			while (!StateSolved())
			{

				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCCW(botCubeC);
				cubeTranslator.TurnRightCCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");

				frontH = StateHeadlights(GREEN, 0);
				rightH = StateHeadlights(WHITE, 0);
				backH = StateHeadlights(BLUE, 0);
				leftH = StateHeadlights(YELLOW, 0);
				frontR = StateRow(GREEN, 0);
				rightR = StateRow(WHITE, 0);
				backR = StateRow(BLUE, 0);
				leftR = StateRow(YELLOW, 0);
				if (frontR && rightR && backR && leftR)
				{
					while (!StateSolved())
					{
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						result.append("U,");
					}
				}
			}
		}
		else if (leftR && frontH)
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			result.append("U,");
			while (!StateSolved())
			{

				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCW(botCubeC);
				cubeTranslator.TurnUpCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCCW(botCubeC);
				cubeTranslator.TurnRightCCW(botCubeG);
				cubeTranslator.TurnUpCCW(botCubeC);
				cubeTranslator.TurnUpCCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				cubeTranslator.TurnRightCW(botCubeC);
				cubeTranslator.TurnRightCW(botCubeG);
				result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");

				frontH = StateHeadlights(GREEN, 0);
				rightH = StateHeadlights(WHITE, 0);
				backH = StateHeadlights(BLUE, 0);
				leftH = StateHeadlights(YELLOW, 0);
				frontR = StateRow(GREEN, 0);
				rightR = StateRow(WHITE, 0);
				backR = StateRow(BLUE, 0);
				leftR = StateRow(YELLOW, 0);
				if (frontR && rightR && backR && leftR)
				{
					while (!StateSolved())
					{
						cubeTranslator.TurnUpCW(botCubeC);
						cubeTranslator.TurnUpCW(botCubeG);
						result.append("U,");
					}
				}
			}
		}
		else if (frontR)
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U,U,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (rightR)
		{
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U1,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (backR)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (leftR)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
	}
	/*while (true)
	{
		for (int i = 0; i < 6; i++)
		{
			if (botCubeC.cube[i].face == solvedCubeC.cube[i].face)
				solved = true;
			else
			{
				solved = false;
				break;
			}
		}
		if (solved)
			break;
		for (int i = 0; i < 4; i++)
		{
			if (botCubeC.cube[(i + 1)].face[0][0] == botCubeC.cube[(i + 1)].face[0][2])
			{
				if (i == 0)
					front = true;
				else if (i == 1)
					right = true;
				else if (i == 2)
					back = true;
				else if (i == 3)
					left = true;
			}
		}
		if (front && right && back && left)
		{
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R,U1,R,U,R,U,R,U1,R1,U1,R,R,");
		}
		else if (front)
		{
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnUpCW(botCubeC);
			cubeTranslator.TurnUpCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U,U,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (right)
		{
			cubeTranslator.TurnUpCCW(botCubeC);
			cubeTranslator.TurnUpCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("U1,R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (back)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else if (left)
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
		else
		{
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnFrontCW(botCubeC);
			cubeTranslator.TurnFrontCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnFrontCCW(botCubeC);
			cubeTranslator.TurnFrontCCW(botCubeG);
			cubeTranslator.TurnRightCCW(botCubeC);
			cubeTranslator.TurnRightCCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnBackCW(botCubeC);
			cubeTranslator.TurnBackCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			cubeTranslator.TurnRightCW(botCubeC);
			cubeTranslator.TurnRightCW(botCubeG);
			result.append("R1,F,R1,B,B,R,F1,R1,B,B,R,R,");
		}
	}*/
	botCubeC.point = resetFace;
	botCubeG.point = resetFace;
	result.append("-,");
	return result;
}

CubeGraph AI::GetGraphicsCube()
{

	return botCubeG;
}

CubeGraph AI::GetColourCube()
{
	return botCubeC;
}

void AI::SetGraphicsCube(CubeGraph _cube)
{
	botCubeG = _cube;
}

void AI::SetColourCube(CubeGraph _cube)
{
	botCubeC = _cube;
}

bool AI::RandomPattern()
{
	//Under Construction
	return false;
}

std::string AI::GetSolveAlgorithm()
{
	if (StateSolved())
		return fullMovelist;
	else
		return notSolved;
}

bool AI::StateBottomCross()
{
	if (botCubeG.cube[5].face[0][1] == solvedCubeG.cube[5].face[0][1] && botCubeG.cube[5].face[1][1] == solvedCubeG.cube[5].face[1][1] && botCubeG.cube[5].face[2][1] == solvedCubeG.cube[5].face[2][1] &&
		botCubeG.cube[5].face[1][0] == solvedCubeG.cube[5].face[1][0] && botCubeG.cube[5].face[1][2] == solvedCubeG.cube[5].face[1][2])
		return true;
	return false;
}

bool AI::StateBottomCorners()
{
	if (botCubeG.cube[5].face[0][0] == solvedCubeG.cube[5].face[0][0] && botCubeG.cube[5].face[0][2] == solvedCubeG.cube[5].face[0][2] && botCubeG.cube[5].face[2][0] == solvedCubeG.cube[5].face[2][0] && botCubeG.cube[5].face[2][2] == solvedCubeG.cube[5].face[2][2])
		return true;
	return false;
}

bool AI::StateMiddleEdges()
{
	if (botCubeG.cube[1].face[1][0] == solvedCubeG.cube[1].face[1][0] && botCubeG.cube[1].face[1][2] == solvedCubeG.cube[1].face[1][2] && botCubeG.cube[3].face[1][0] == solvedCubeG.cube[3].face[1][0] && botCubeG.cube[3].face[2][1] == solvedCubeG.cube[3].face[2][1])
		return true;
	return false;
}

bool AI::StateTopCross()
{
	if (botCubeC.cube[0].face[0][1] == solvedCubeC.cube[0].face[0][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[2][1] == solvedCubeC.cube[0].face[2][1] &&
		botCubeC.cube[0].face[1][0] == solvedCubeC.cube[0].face[1][0] && botCubeC.cube[0].face[1][2] == solvedCubeC.cube[0].face[1][2])
		return true;
	return false;
}

bool AI::StateTopVert()
{
	if (botCubeC.cube[0].face[0][1] == solvedCubeC.cube[0].face[0][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[2][1] == solvedCubeC.cube[0].face[2][1])
		return true;
	return false;
}

bool AI::StateTopHor()
{
	if (botCubeC.cube[0].face[1][0] == solvedCubeC.cube[0].face[1][0] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][2] == solvedCubeC.cube[0].face[1][2])
		return true;
	return false;
}

bool AI::StateTopLeftL()
{
	if (botCubeC.cube[0].face[0][1] == solvedCubeC.cube[0].face[0][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][0] == solvedCubeC.cube[0].face[1][0])
		return true;
	return false;
}

bool AI::StateTopRightL()
{
	if (botCubeC.cube[0].face[0][1] == solvedCubeC.cube[0].face[0][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][2] == solvedCubeC.cube[0].face[1][2])
		return true;
	return false;
}

bool AI::StateTopBotLeftL()
{
	if (botCubeC.cube[0].face[2][1] == solvedCubeC.cube[0].face[2][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][0] == solvedCubeC.cube[0].face[1][0])
		return true;
	return false;
}

bool AI::StateTopBorRightL()
{
	if (botCubeC.cube[0].face[2][1] == solvedCubeC.cube[0].face[2][1] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][2] == solvedCubeC.cube[0].face[1][2])
		return true;
	return false;
}

bool AI::StateTopCenter()
{
	if (botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1])
		return true;
	return false;
}

bool AI::StateOriented()
{
	if (botCubeC.cube[0].face[0][0] == solvedCubeC.cube[0].face[0][0] && botCubeC.cube[0].face[0][1] == solvedCubeC.cube[0].face[0][1] && botCubeC.cube[0].face[0][2] == solvedCubeC.cube[0].face[0][2] &&
		botCubeC.cube[0].face[1][0] == solvedCubeC.cube[0].face[1][0] && botCubeC.cube[0].face[1][1] == solvedCubeC.cube[0].face[1][1] && botCubeC.cube[0].face[1][2] == solvedCubeC.cube[0].face[1][2] &&
		botCubeC.cube[0].face[2][0] == solvedCubeC.cube[0].face[2][0] && botCubeC.cube[0].face[2][1] == solvedCubeC.cube[0].face[2][1] && botCubeC.cube[0].face[2][2] == solvedCubeC.cube[0].face[2][2])
		return true;
	return false;
}

bool AI::StatePermuted()
{
	bool skip = false;
	if (StateSolved())
		skip = true;
	else
		skip = false;
	return skip;
}

bool AI::StateSolved()
{
	bool solved = false;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			if (botCubeC.cube[i].face[botCubeC.calculator.From1Dto2D(j, 3, i).x][botCubeC.calculator.From1Dto2D(j, 3, i).y] == solvedCubeC.cube[i].face[solvedCubeC.calculator.From1Dto2D(j, 3, i).x][solvedCubeC.calculator.From1Dto2D(j, 3, i).y])
				solved = true;
			else
			{
				solved = false;
				break;
			}
		}
		if (solved == false)
			break;
	}
	return solved;
}
bool AI::StateRow(int face, int row)
{
	if (botCubeC.cube[face].face[row][0] == botCubeC.cube[face].face[row][1] && botCubeC.cube[face].face[row][1] == botCubeC.cube[face].face[row][2])
		return true;
	return false;
}
bool AI::StateHeadlights(int face, int row)
{
	if (botCubeC.cube[face].face[row][0] == botCubeC.cube[face].face[row][2] && !(botCubeC.cube[face].face[row][1] == botCubeC.cube[face].face[row][2]))
		return true;
	return false;
}
std::vector<VRInput> AI::GetSolveVRInput()
{
	std::string temp;
	char letter;
	movelist.resize(fullMovelist.size());
	int counter = 0;
	for (int i = 0; i < fullMovelist.size(); i++)
	{

		if (!(fullMovelist[i] == ','))
			temp.push_back(fullMovelist[i]);
		else if (fullMovelist[i] == ',')
		{
			if (temp == "R")
			{
				movelist[counter].R = true;
			}
			else if (temp == "R1")
			{
				movelist[counter].R1 = true;
			}
			if (temp == "F")
			{
				movelist[counter].F = true;
			}
			if (temp == "F1")
			{
				movelist[counter].F1 = true;
			}
			if (temp == "U")
			{
				movelist[counter].U = true;
			}
			if (temp == "U1")
			{
				movelist[counter].U1 = true;
			}
			if (temp == "L")
			{
				movelist[counter].L = true;
			}
			if (temp == "L1")
			{
				movelist[counter].L1 = true;
			}
			if (temp == "D")
			{
				movelist[counter].D = true;
			}
			if (temp == "D1")
			{
				movelist[counter].D1 = true;
			}
			if (temp == "B")
			{
				movelist[counter].B = true;
			}
			if (temp == "B1")
			{
				movelist[counter].B1 = true;
			}
			if (temp == ">")
			{
				movelist[counter].rotateRight = true;
			}
			if (temp == "<")
			{
				movelist[counter].rotateLeft = true;
			}
			if (temp == "-")
			{
				movelist[counter].resetFront = true;
			}
			temp.clear();
			counter += 1;
		}
	}
	movelist.resize(counter);
	return movelist;
}
AI::~AI()
{
}

