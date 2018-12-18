#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "MainCamera.h"

class MyShader
{
public:
	MyShader();

	void BindShader(); //Set gpu to use our shaders
	void Update(const TransformStruct& transform, const MainCamera& camera);
	void init(const std::string& filename);

	std::string MyShader::LoadShader(const std::string& fileName);
	void MyShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint MyShader::CreateShader(const std::string& text, unsigned int type);

    ~MyShader();


protected:
private:
	static const unsigned int NUMBoF_SHADERS = 2; // number of shaders

	//uniforms
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUMBoF_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
