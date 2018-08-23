#include "stdafx.h"
#include "MeshLoader.h"


std::vector<std::string> MeshLoader::GetMeshList(const char* filename)
{
	std::vector<std::string> meshList;
	FILE *info;
	std::string tempString;
	char letter;
	fopen_s(&info, filename, "rb");
	if (info)
	{
		while (!feof(info))
		{

			fread(&letter, sizeof(char), 1, info);
			if (letter != ',')
			{
				tempString.push_back(letter);
			}
			else if (letter == ',')
			{
				meshList.push_back(tempString);
				tempString.clear();
			}
		}
	fclose(info);
	}
	return meshList;
}

Mesh MeshLoader::ReadMesh(const char * filepath)
{
	FILE* info;
	fopen_s(&info, filepath, "rb");
	Mesh fileMesh;
	int size = 0;
	if (info)
	{
		Mesh temp;
		fread(&size, sizeof(size), 1, info);
		temp.verts.resize(size);
		for (int i = 0; i < size; i++)
		{
			fread(&temp.verts[i].position, sizeof(temp.verts[i].position), 1, info);
			fread(&temp.verts[i].normals, sizeof(temp.verts[i].normals), 1, info);
			fread(&temp.verts[i].uv, sizeof(temp.verts[i].uv), 1, info);
			temp.indices.push_back(size);
		}
		fileMesh = temp;
	fclose(info);
	}
	return fileMesh;
}

void MeshLoader::ReadMaterial(char * filepath)
{
	/*FILE* info = fopen(filepath, "rb");
	if (info)
	{
		int size = 0;
		int pathlength = 0;
		char current;
		fread(&size, sizeof(int), 1, info);
		material.reserve(size);
		BasicMaterial temp;

		for (int i = 0; i < size; i++)
		{

			fread(&temp.value, sizeof(temp.value), 1, info);
			fread(&pathlength, sizeof(int), 1, info);

			char strung[100];
			std::string s;
			for (int j = 0; j < pathlength; j++)
			{

				fread(&current, sizeof(char), 1, info);

				strung[j] = current;
				s.push_back(current);
				if ((j + 1) == pathlength)
					strung[j + 1] = '\x0';
			}

			std::wstring* texturePath = new std::wstring(s.begin(), s.end());
			if (i == 0)
			{
				diffusePath = texturePath->c_str();
				hasDiffuse = true;
			}
			else if (i == 1)
			{
				emissivePath = texturePath->c_str();
				hasEmissive = true;
			}
			else if (i == 2)
			{
				specularPath = texturePath->c_str();
				hasSpecular = true;
			}
			else if (i == 3)
			{
				normalPath = texturePath->c_str();
				hasNormal = true;
			}

			material.push_back(temp);
		}
	}
	fclose(info);

	if (hasDiffuse)
	{

		diffuse.x = material[0].value[0];
		diffuse.y = material[0].value[1];
		diffuse.z = material[0].value[2];
	}

	if (hasEmissive)
	{

		emissive.x = material[1].value[0];
		emissive.y = material[1].value[1];
		emissive.z = material[1].value[2];
	}

	if (hasSpecular)
	{

		specular.x = material[2].value[0];
		specular.y = material[2].value[1];
		specular.z = material[2].value[2];
	}

	if (hasSpecular)
		shine = material[3].value[0];

	for (int i = 0; i < material.size(); i++)
	{
		printf("\n %f", material[i].value[0]);
		printf("\n %f", material[i].value[1]);
		printf("\n %f", material[i].value[2]);
		printf("\n %f", material[i].value[3]);
	}*/
}
