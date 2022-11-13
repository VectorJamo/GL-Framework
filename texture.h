#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../externals/stb_image/stb_image.h"

class Texture
{
private:
	unsigned int pTextureID;
	std::string pTexturePath;
	unsigned char* pPixelBuffer;
	int pWidth, pHeight, pChannels;

public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind(unsigned int slot = 0) const;
};

