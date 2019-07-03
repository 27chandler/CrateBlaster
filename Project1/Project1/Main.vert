#version 400
//vertex shader

in vec3 vertexIn;
in vec3 colourIn;
in vec3 normalIn;
//in float counterIn;
in vec2 textureIn;

out vec3 colourOut;
out vec2 textureOut;
out vec3 vertexOut;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat3 normal_mat;



void main(void)
{
	textureOut = textureIn;
	colourOut = colourIn;
	normalOut = normal_mat * normalIn;
	vertexOut = (model * vec4(vertexIn,1.0)).xyz;
	gl_Position = proj * view * model * vec4(vertexIn,1.0f);
}

