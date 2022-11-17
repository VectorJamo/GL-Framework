#pragma once

#include "shader.h"
#include "texture.h"
#include "../maths/vec/vec2.h"
#include "../maths/vec/vec4.h"
#include "../maths/mat/mat4.h"

struct Color
{
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a);
};
struct GLObject
{
	unsigned int vao, vbo, ibo;
	Shader* shader;
};

class  Rect
{
private:
	GLObject pObject;
	Texture* pTexture;

	vec2 pPosition, pSize;
	Color pColor;

private:
	void CreateRect();

public:
	Rect(int x, int y, int width, int height);
	~Rect();

	void Draw();
	void Draw(Shader* shader);
	
	// Setters
	void SetTexture(const char* texturePath);
	void SetPosition(const vec2& pos);
	void SetSize(const vec2& size);
	void SetColor(const Color& color);

	// Getters
	inline vec2 GetPosition() { return pPosition; }
	inline vec2 GetSize() { return pSize; }
	inline Color GetColor() { return pColor; }
};
