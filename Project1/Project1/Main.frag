#version 400
//fragment shader

in vec3 colourOut;
in vec2 textureOut;
in vec3 vertexOut;
in vec3 normalOut;

out vec4 pixelColour;

void Calculate_Diffuse();
void Calculate_Ambient();
void Calculate_Specular();
float Calculate_Attenuation();

uniform sampler2D textureImage;

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	float constant;
	float quadratic;
	float linear;
};

struct Material
{
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
};

uniform Light the_light[41];
uniform Material the_material;
uniform vec3 cam_pos;

uniform bool is_lit;
uniform bool is_textured;
uniform bool is_toon;

uniform int total_lights;

uniform mat4 model;

vec3 normals;
vec3 vertex_pos;
vec3 light_dir;
float light_intensity;

vec3 diffuse_colour;
vec3 ambient_colour;
vec3 specular_colour;

int light_number = 0;

void main(void)
{
	if (is_lit)
	{
		normals = normalize(normalOut);
		if (is_textured)
		{
			for (light_number = 0; light_number < total_lights; light_number++)
			{
				Calculate_Diffuse();
				Calculate_Ambient();
				Calculate_Specular();
				pixelColour += vec4(((ambient_colour + ((diffuse_colour + specular_colour) * Calculate_Attenuation()))),1.0f) * texture(textureImage, textureOut);

				if (is_toon)
				{

					//float red = float(round(pixelColour.r));
					//float blue = float(round(pixelColour.b));
					//float green = float(round(pixelColour.g));

					float red = 1.0f-(pixelColour.r);
					float blue = 1.0f-(pixelColour.b);
					float green = 1.0f-(pixelColour.g);

					pixelColour = vec4(red,blue,green,1.0f);


					//float red = pixelColour.r;
					//float blue = pixelColour.b;
					//float green = pixelColour.g;

					//if ((green > red) && (green > blue))
					//{
					//	pixelColour = vec4(0.0f,1.0f,0.0f,1.0f);
					//}
					//else if ((red > green) && (red > blue))
					//{
					//	pixelColour = vec4(1.0f,0.0f,0.0f,1.0f);
					//}
					//else if ((blue > red) && (blue > green))
					//{
					//	pixelColour = vec4(0.0f,0.0f,1.0f,1.0f);
					//}
					//else
					//{
					//	pixelColour = vec4(0.7f,0.7f,0.7f,1.0f);
					//}
				}
				//textureOut = textureIn;
			}
		}
		else
		{
			for (light_number = 0; light_number < total_lights; light_number++)
			{
				Calculate_Diffuse();
				Calculate_Ambient();
				Calculate_Specular();
				pixelColour +=  vec4(((ambient_colour + ((diffuse_colour + specular_colour) * Calculate_Attenuation()))),1.0f);

			}
		}
	}
	else
	{
		if (is_textured)
		{
			// apply texture and colours
			pixelColour = vec4(colourOut,1.0) * texture(textureImage, textureOut);
		}
		else
		{
			pixelColour = vec4(colourOut,1.0);
		}
	}
}

float Calculate_Attenuation()
{


	float attenuation_return = 0;

	// 1 / constant + linear * distance + quadratic * distance squared
	float light_distance = length(the_light[light_number].position - vertexOut);

	attenuation_return = (1.0 / (the_light[light_number].constant + (the_light[light_number].linear * light_distance) + (the_light[light_number].quadratic * (light_distance * light_distance))));

	return attenuation_return;
}

void Calculate_Diffuse()
{
	//diffuse_colour = vec3(0.0f,0.0f,0.0f);
	// -------------------------------------------------------------
	// Diffuse colour value
	// Normal
	light_dir = normalize(the_light[light_number].position - vertexOut);

	light_intensity = max(dot(light_dir,normals),0.0);

	diffuse_colour = the_light[light_number].diffuse * the_material.diffuse * light_intensity;

	// -------------------------------------------------------------
}

void Calculate_Ambient()
{
	//ambient_colour = vec3(0.0f,0.0f,0.0f);

	// -------------------------------------------------------------
	// Ambient colour value
	ambient_colour = the_light[light_number].ambient * the_material.ambient;

	// -------------------------------------------------------------

}

void Calculate_Specular()
{
	//specular_colour = vec3(0.0f,0.0f,0.0f);
	
	// -------------------------------------------------------------
	// Specular colour value

	vec3 view_dir = normalize(cam_pos - vertexOut);
	vec3 reflection = reflect(-light_dir, normals);

	float spec_term = pow(max(dot(view_dir, reflection), 0.0),the_material.shininess);

	specular_colour = the_light[light_number].specular * the_material.specular * spec_term;

	// -------------------------------------------------------------

}