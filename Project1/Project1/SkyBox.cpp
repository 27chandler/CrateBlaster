#include "SkyBox.h"



Skybox::Skybox()
{
	is_lit = 0;
	is_textured = 1;

	//-----------------------------------------

	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
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

	for (int i = 0; i < 24; i++)
	{
		colours.push_back(1.0f);
		colours.push_back(1.0f);
		colours.push_back(1.0f);
	}

	// uvs are set up to mostly be in line with each other
	uvs.push_back(0.0f);  // bottom left x Forward side flipper horizontal
	uvs.push_back(0.4f);  // bottom left y
	uvs.push_back(0.25f); // bottom right x
	uvs.push_back(0.4f);  // bottom right y
	uvs.push_back(0.25f); // top right x
	uvs.push_back(0.6666f);  // top right y
	uvs.push_back(0.0f);  // top left x
	uvs.push_back(0.6666f);  // top right y

	uvs.push_back(0.75f); // bottom left x back side
	uvs.push_back(0.4f); // bottom left y
	uvs.push_back(0.5f); // bottom right x
	uvs.push_back(0.4f); // bottom right y
	uvs.push_back(0.5f); // top right x
	uvs.push_back(0.6666f); // top right y
	uvs.push_back(0.75f); // top left x
	uvs.push_back(0.6666f); // top right y

	uvs.push_back(0.75f); // right side
	uvs.push_back(0.4f);
	uvs.push_back(1.0f);
	uvs.push_back(0.4f);
	uvs.push_back(1.0f);
	uvs.push_back(0.666f);
	uvs.push_back(0.75f);
	uvs.push_back(0.666f);

	uvs.push_back(0.5f); // bottom left x left side
	uvs.push_back(0.4f); // bottom left y
	uvs.push_back(0.25f);// bottom right x
	uvs.push_back(0.4f); // bottom right y
	uvs.push_back(0.25f);// top right x
	uvs.push_back(0.6666f); // top right y
	uvs.push_back(0.5f); // top left x
	uvs.push_back(0.6666f); // top right y


	uvs.push_back(0.5f); // bottom right x
	uvs.push_back(0.0f);  // bottom right y
	uvs.push_back(0.5f); // top right x
	uvs.push_back(0.4f);  // top right y
	uvs.push_back(0.25f);// top left x
	uvs.push_back(0.4f);  // top left y
	uvs.push_back(0.25f);// bottom left x top side flipper horizontal
	uvs.push_back(0.0f);  // bottom left y

	uvs.push_back(0.5f); // bottom right x
	uvs.push_back(1.0f);  // bottom right y
	uvs.push_back(0.5f); // top right x
	uvs.push_back(0.6666f);  // top right y
	uvs.push_back(0.25f);// top left x
	uvs.push_back(0.6666f);  // top left y
	uvs.push_back(0.25f);// bottom left x bottom side flipper horizontal
	uvs.push_back(1.0f);  // bottom left y

	for (int i = 0; i < 6; i++)
	{
		indices.push_back(0 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(2 + (i * 4));
	}

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			normals.push_back(0.0f);
			normals.push_back(0.0f);
			normals.push_back(1.0f);
		}
	}
}
