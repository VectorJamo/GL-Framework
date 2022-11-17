#include "primitives.h"

Color::Color()
    :r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{

}
Color::Color(float r, float g, float b, float a)
    :r(r), g(g), b(b), a(a)
{
}

Rect::Rect(int x, int y, int width, int height)
	:pTexture(nullptr), pPosition(x, y), pSize(width, height)
{
	pObject.vao = 0; pObject.vbo = 0; pObject.ibo = 0; pObject.shader = nullptr;
	pColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	CreateRect();
}

Rect::~Rect()
{
	if (pTexture != nullptr)
		delete pTexture;

	delete pObject.shader;
}

void Rect::CreateRect()
{
	// Create the vao, vbo, ibo, shader
    float positions[8] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    unsigned char indices[6] = {
        0, 1, 2, 2, 0, 3
    };

    glGenVertexArrays(1, &pObject.vao);
    glBindVertexArray(pObject.vao);

    glGenBuffers(1, &pObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, pObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, positions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glGenBuffers(1, &pObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char) * 6, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    pObject.shader = new Shader("src/shaders/vs.glsl", "src/shaders/fs.glsl");
    pObject.shader->Bind();

    mat4 projection = orthographic(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    pObject.shader->SetUniformMat4f("uProjection", projection);

    SetPosition(pPosition);
    SetSize(pSize);
    
    SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    pObject.shader->SetUniform1i("uUseTexture", 0);
    pObject.shader->Unbind();
}

void Rect::Draw()
{
    glBindVertexArray(pObject.vao);
    pObject.shader->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Rect::Draw(Shader* shader)
{
    glBindVertexArray(pObject.vao);
    shader->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Rect::SetTexture(const char* texturePath)
{
    float textCoords[8] =
    {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    unsigned int vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, textCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(pObject.vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    pTexture = new Texture(texturePath);

    pObject.shader->Bind();
    pTexture->Bind(0);
    pObject.shader->SetUniform1i("uUseTexture", 1);
    pObject.shader->Unbind();
}

void Rect::SetPosition(const vec2& pos)
{
    pPosition = pos;
    mat4 translation = translate(vec3(pos.x, pos.y, 0.0f));

    pObject.shader->Bind();
    pObject.shader->SetUniformMat4f("uTranslation", translation);
    pObject.shader->Unbind();
}

void Rect::SetSize(const vec2& size)
{
    pSize = size;
    mat4 scaleMat = scale(vec3(size.x, size.y, 1.0f));\

    pObject.shader->Bind();
    pObject.shader->SetUniformMat4f("uScale", scaleMat);
    pObject.shader->Unbind();
}

void Rect::SetColor(const Color& color)
{
    pColor = color;
    pObject.shader->Bind();
    pObject.shader->SetUniformColor4f("uColor", color);
    pObject.shader->Unbind();
}
