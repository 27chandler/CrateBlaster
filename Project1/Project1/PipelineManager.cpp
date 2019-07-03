#include "PipelineManager.h"

PipelineManager::PipelineManager()
{
	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
}

bool PipelineManager::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (!m_shaderProgramID)
	{
		std::cout << "Error" << std::endl;
		return false;
	}

	return true;
}

bool PipelineManager::CreateShaders()
{

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vertexShaderID)
	{
		std::cout << "Error creating vert shader" << std::endl;
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	return true;
}

bool PipelineManager::CompileShader(std::string filename, GLuint shader_id)
{
	std::fstream file;
	std::string line = "";
	std::string finalstring = "";
	//-----Vert Shader-----
	//---------------------
	file.open(filename);

	if (!file)
	{
		std::cout << filename << ": File could not be opened!" << std::endl;
	}

	while (!file.eof())
	{
		getline(file, line);
		finalstring += line + "\n";
	}
	file.close();

	// convert to GLchar c-style string
	const GLchar* finalcode = (const GLchar*)(finalstring.c_str());

	// bind source code to vert shader object
	glShaderSource(shader_id, 1, &finalcode, NULL);

	// compile source code
	glCompileShader(shader_id);

	GLint compileresult;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileresult);

	if (compileresult == GL_TRUE)
	{
		std::cout << filename << " shader compiled ok!" << std::endl;
	}
	else
	{		
		// error trap
		GLchar error[1000];
		GLint length = 1000;

		glGetShaderInfoLog(shader_id, 2000, &length, error);



		std::cout << filename << " shader did not compile!" << std::endl;
		std::cout << error << std::endl;
	}


	// Reset variables
	line = "";
	finalstring = "";
	return true;

}

GLuint PipelineManager::GetProgramID()
{
	return m_shaderProgramID;
}

GLuint PipelineManager::GetFragID()
{
	return m_fragmentShaderID;
}

GLuint PipelineManager::GetVertID()
{
	return m_vertexShaderID;
}



void PipelineManager::AttachShaders()
{
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
}

bool PipelineManager::LinkProgram()
{

	// links shader program
	glLinkProgram(m_shaderProgramID);

	// uses shader program
	glUseProgram(m_shaderProgramID);

	GLint linkresult;

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkresult);

	if (linkresult == GL_TRUE)
	{
		std::cout << "Shader program linked!" << std::endl;

	}
	else
	{
		// error trap
		GLchar error[1000];
		GLsizei length = 1000;

		glGetProgramInfoLog(m_shaderProgramID, 2000, &length, error);



		std::cout << "Shader program did not link!" << std::endl;
		std::cout << error << std::endl;
	}


	return true;
}

void PipelineManager::DetachShaders()
{
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
}



void PipelineManager::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}

void PipelineManager::DestroyShaders()
{
	glDeleteShader(m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
}
