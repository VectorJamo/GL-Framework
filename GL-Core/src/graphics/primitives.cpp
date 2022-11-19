#include "primitives.h"

#include "../maths/constants.h"

Color::Color()
    :r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{}
Color::Color(float r, float g, float b, float a)
    :r(r), g(g), b(b), a(a)
{}

GLObject::GLObject()
    :vao(0), vbo(0), ibo(0)
{}

Shader* Sprite::pShader = nullptr;
Sprite::Sprite(int x, int y, int width, int height)
	:pTexture(nullptr), pPosition(x, y), pSize(width, height), pTextCoordVBO(0)
{
    if (!OrthographicCamera::IsCameraInitialized())
    {
        std::cout << "Initialize a camera before rendering anything!" << std::endl;
        assert(false);
    }
    else {
        CreateRect();
    }
}

Sprite::~Sprite()
{
	if (pTexture != nullptr)
		delete pTexture;
}
void Sprite::Free()
{
    delete pShader;
}

void Sprite::CreateRect()
{
    float positions[8] =
    {
        -1.0f,   1.0f,
        -1.0f,  -1.0f,
         1.0f,  -1.0f,
         1.0f,   1.0f
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

    SetSize(pSize);
    SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void Sprite::Draw()
{
    glBindVertexArray(pObject.vao);
    pShader->Bind();
    // Create the model view matrix
    pModelView = (pTranslation * OrthographicCamera::GetCameraTranslationMatrix()) * (OrthographicCamera::GetCameraRotationMatrix() * pRotation) * pScale;

    if (pTexture == nullptr)
    {
        pShader->SetUniformMat4f("uProjection", OrthographicCamera::GetProjectionMatrix());
        pShader->SetUniformMat4f("uModelView", pModelView);
        pShader->SetUniform1i("uUseTexture", 0);
        pShader->SetUniformColor4f("uColor", pColor);
    }
    else
    {
        pShader->SetUniformMat4f("uProjection", OrthographicCamera::GetProjectionMatrix());
        pShader->SetUniformMat4f("uModelView", pModelView);
        pTexture->Bind(0);
        pShader->SetUniform1i("uUseTexture", 1);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void Sprite::Init()
{
    pShader = new Shader("src/shaders/vs.glsl", "src/shaders/fs.glsl");
}

void Sprite::SetTexture(const char* texturePath)
{
    float textCoords[8] =
    {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenBuffers(1, &pTextCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pTextCoordVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, textCoords, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(pObject.vao);

    glBindBuffer(GL_ARRAY_BUFFER, pTextCoordVBO);
 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    pTexture = new Texture(texturePath);
}

void Sprite::SetPosition(const vec2& pos)
{
    pPosition = pos;
    pTranslation = translate(vec3(pos.x + pSize.x/2, pos.y - pSize.y/2, 0.0f));
}

void Sprite::SetSize(const vec2& size)
{
    pSize = size;
    pScale = scale(vec3(size.x/2, size.y/2, 1.0f)); // The size has to be divided by 2 because it is scaled evenly both on right and left
    
    SetPosition(pPosition);
}

void Sprite::SetRotation(const float& angle)
{
    pRotation = rotate(-TO_RADIANS(angle), vec3(0.0f, 0.0f, 1.0f));
}

void Sprite::SetColor(const Color& color)
{
    pColor = color;
}

void Sprite::SetTextureClipRect(int x, int y, int width, int height)
{
    float newTextCoords[8] =
    {
                x / (float)(pTexture->GetWidth())                ,       ((pTexture->GetHeight()) - y) / (float)(pTexture->GetHeight()),
                x / (float)(pTexture->GetWidth())                ,       ((pTexture->GetHeight()) - (y + height)) / (float)(pTexture->GetHeight()),
               (x + width) / (float)(pTexture->GetWidth())       ,      ((pTexture->GetHeight()) - (y + height)) / ((float)pTexture->GetHeight()),
               (x + width) / (float)(pTexture->GetWidth())       ,      ((pTexture->GetHeight() - y) / (float)(pTexture->GetHeight())),
    };

    glBindBuffer(GL_ARRAY_BUFFER, pTextCoordVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, newTextCoords);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
