#include "Quad.h"

Quad::Quad()
{
	vertices.push_back(-0.5f); //x
	vertices.push_back(0.5f); //y
	vertices.push_back(0.0f); //z
	vertices.push_back(0.5f); //x2
	vertices.push_back(0.5f); //y2
	vertices.push_back(0.0f); //z2

	vertices.push_back(0.5f); //x
	vertices.push_back(-0.5f); //y
	vertices.push_back(0.0f); //z
	vertices.push_back(-0.5f); //x2
	vertices.push_back(-0.5f); //y2
	vertices.push_back(0.0f); //z2

	for (int i = 0; i < 12; i++)
	{
		colours.push_back(1.0f);
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);

	uvs.push_back(0.0f);
	uvs.push_back(0.0f);
	uvs.push_back(1.0f);
	uvs.push_back(0.0f);
	uvs.push_back(1.0f);
	uvs.push_back(1.0f);
	uvs.push_back(0.0f);
	uvs.push_back(1.0f);

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(-1.0f);
	}
}