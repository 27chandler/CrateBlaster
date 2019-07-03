#include "CubeObject.h"

CubeObject::CubeObject()
{
	is_lit = 1;
	is_textured = 1;

	obj_material.Set_Ambient(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Diffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Specular(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Shininess(32.0f);

	//-----------------------------------------

	//------------------------
	vertices.push_back(-0.5f); //x
	vertices.push_back(0.5f); //y
	vertices.push_back(0.5f); //z
	vertices.push_back(0.5f); //x2
	vertices.push_back(0.5f); //y2
	vertices.push_back(0.5f); //z2
	//------------------------
	//------------------------
	vertices.push_back(0.5f); // Back
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	//------------------------

	for (int i = 0; i < 4; i++) //
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(1.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(-1.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(-1.0f);
		normals.push_back(0.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(1.0f);
		normals.push_back(0.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(1.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(-1.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 24; i++)
	{
		colours.push_back(1.0f);
		colours.push_back(0.0f);
		colours.push_back(0.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		uvs.push_back(0.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
		uvs.push_back(1.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		indices.push_back(0 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(2 + (i * 4));
	}

	//for (int i = 0; i < 6; i++)
	//{
	//	normals.push_back(1.0f);
	//}



	//int i = 0;
	//while (i != vertices.size())
	//{
	//	std::cout << "1: " << vertices[i] << std::endl;
	//	i++;
	//}
	//system("PAUSE");
}
