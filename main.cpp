#include "window.h"
#include "shader.h"
#include "texture.h"
#include "error handling.h"

int main()
{
    Window window(800, 600, "OpenGL Window");
    if (!window.Init())
    {
        std::cin.get();
        return -1;
    }
    window.SetVSyncEnabled(true);
    
    float vertices[4*4] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    unsigned short indices[6] = { 
        0, 1, 2, 2, 0, 3 
    };

    unsigned int vao, vbo, ibo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float)*2));

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shader("shaders/vs.glsl", "shaders/fs.glsl");
    shader.Bind();
    shader.SetUniform1i("uTextureUnit", 0);
    shader.Unbind();

    Texture texture("textures/among us.png");
    texture.Bind(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    while (!window.IsClosed())
    {
        window.Clear(0.7f, 0.0f, 0.8f, 1.0f);
        window.PollEvents();

        // Draw
        glBindVertexArray(vao);
        shader.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        window.Display();
    }

    return 0;
}
