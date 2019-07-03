#include "Material.h"

#include "PipelineManager.h"

void Material::Init()
{
	program_id = ThePipeline::Instance()->GetProgramID();

	light_flag_id = glGetUniformLocation(program_id, "is_lit");
	toon_flag_id = glGetUniformLocation(program_id, "is_toon");

	material_ambient_id = glGetUniformLocation(program_id, "the_material.ambient");
	material_diffuse_id = glGetUniformLocation(program_id, "the_material.diffuse");
	material_specular_id = glGetUniformLocation(program_id, "the_material.specular");
	material_shininess_id = glGetUniformLocation(program_id, "the_material.shininess");
}

void Material::Send_Data(bool is_lit_input,bool is_toon_input)
{
	if (is_lit_input == 1)
	{
		glUniform1i(light_flag_id, true);

		glUniform1fv(material_shininess_id, 1, &shininess);
		glUniform3fv(material_ambient_id, 1, &ambient.r);
		glUniform3fv(material_diffuse_id, 1, &diffuse.r);
		glUniform3fv(material_specular_id, 1, &specular.r);
	}
	else
	{
		glUniform1i(light_flag_id, false);
	}

	if (is_toon_input == 1)
	{
		glUniform1i(toon_flag_id, true);
	}
	else
	{
		glUniform1i(toon_flag_id, false);
	}
}
