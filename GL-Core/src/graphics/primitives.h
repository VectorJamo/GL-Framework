#pragma once

#include "shader.h"
#include "texture.h"
#include "../maths/vec/vec2.h"
#include "../maths/vec/vec4.h"
#include "../maths/mat/mat4.h"

#include "../util/orthographic_camera.h"
#include <cassert>

struct Color
{
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a);
};
struct GLObject
{
	unsigned int vao, vbo, ibo;

	GLObject();
};

class Sprite
{
private:
	// Sprite's data
	GLObject pObject;
	static Shader* pShader;
	unsigned int pTextCoordVBO;
	Texture* pTexture;

	// Sprite's transform
	vec2 pPosition, pSize;
	Color pColor;

	// Sprite's transform matrices
	mat4 pTranslation, pRotation, pScale;
	mat4 pModelView;

private:
	void CreateRect();

public:
	Sprite(int x, int y, int width, int height);
	~Sprite();

	void Draw();
	
	static void Init();
	static void Free();

	// Setters
	void SetTexture(const char* texturePath);
	void SetPosition(const vec2& pos);
	void SetSize(const vec2& size);
	void SetRotation(const float& angle);
	void SetColor(const Color& color);
	void SetTextureClipRect(int x, int y, int width, int height);

	// Getters
	inline vec2 GetPosition() { return pPosition; }
	inline vec2 GetSize() { return pSize; }
	inline Color GetColor() { return pColor; }
};
