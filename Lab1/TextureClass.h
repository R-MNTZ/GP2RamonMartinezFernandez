#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

class TextureClass
{
public:
	TextureClass();

	void TexBind(unsigned int unit); // bind upto 32 textures
	void initTex(const std::string& fileName);
	~TextureClass();

protected:
private:

	//Handle to refer to the textures by
	GLuint texHandler;
};

