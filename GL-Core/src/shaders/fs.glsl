#version 330 core

uniform vec4 uColor;
out vec4 uFragColor;

in vec2 vTextCoord;
uniform int uUseTexture;
uniform sampler2D uTextureUnit;

void main()
{
	if(uUseTexture == 1)
	{
		uFragColor = texture(uTextureUnit, vTextCoord);
	}else {
		uFragColor = uColor;
	}
}