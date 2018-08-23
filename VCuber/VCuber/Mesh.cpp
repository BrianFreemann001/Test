#include "stdafx.h"
#include "Mesh.h"

Vertex Vertex::operator+(Vertex b)
{
	Vertex temp;

	temp.position.x = position.x + b.position.x;
	temp.position.y = position.y + b.position.y;
	temp.position.y = position.y + b.position.y;
	return(temp);
}

Vertex Vertex::operator-(Vertex b)
{
	Vertex temp;

	temp.position.x = position.x - b.position.x;
	temp.position.y = position.y - b.position.y;
	temp.position.y = position.y - b.position.y;
	return(temp);
}

Vertex Vertex::operator*(Vertex b)
{
	Vertex temp;

	temp.position.x = position.x * b.position.x;
	temp.position.y = position.y * b.position.y;
	temp.position.y = position.y * b.position.y;
	return(temp);
}

Vertex Vertex::operator/(Vertex b)
{
	Vertex temp;

	temp.position.x = position.x / b.position.x;
	temp.position.y = position.y / b.position.y;
	temp.position.y = position.y / b.position.y;
	return(temp);
}
