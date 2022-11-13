#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* pWindow;
    static int pWidth, pHeight;
    const char* pTitle;

public:
    Window(int width, int height, const char* title);
    ~Window();

    bool Init();
    bool IsClosed();

    void PollEvents();
    void Clear(float r, float g, float b, float a);
    void Display();

    // Setters
    void SetVSyncEnabled(bool status);

    // Getters
    inline int GetWidth() const { return pWidth; }
    inline int GetHeight() const { return pHeight; }
    inline const GLFWwindow* GetWindowObject() const { return pWindow; }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
