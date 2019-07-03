#ifndef PIPELINEMANAGER_H
#define PIPELINEMANAGER_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Singleton.h"

class PipelineManager
{

public:

	friend class Singleton<PipelineManager>;

	
	GLuint GetProgramID();

	GLuint GetFragID();

	GLuint GetVertID();

	bool CreateProgram();

	bool CreateShaders();

	bool CompileShader(std::string filename, GLuint shader_id);

	void AttachShaders();

	bool LinkProgram();

	void DetachShaders();

	void DestroyProgram();

	void DestroyShaders();



	PipelineManager();
	PipelineManager(const PipelineManager&);
	PipelineManager& operator=(PipelineManager&);


private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};


typedef Singleton<PipelineManager> ThePipeline;

#endif