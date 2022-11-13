#include "window.h"

int Window::pWidth;
int Window::pHeight;

Window::Window(int width, int height, const char* title)
    :pWindow(nullptr), pTitle(title)
{
    pWidth = width;
    pHeight = height;
}

Window::~Window()
{
    glfwTerminate();
}
bool Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(pWidth, pHeight, pTitle, NULL, NULL);
    if(pWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(pWindow);
    glfwSetKeyCallback(pWindow, key_callback);
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        return false;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    return true;
}
bool Window::IsClosed()
{
    return glfwWindowShouldClose(pWindow);
}
void Window::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Window::PollEvents()
{
    glfwPollEvents();
}
void Window::Display()
{
    glfwSwapBuffers(pWindow);
}
void Window::SetVSyncEnabled(bool status)
{
    glfwSwapInterval(status);
}
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    pWidth = width;
    pHeight = height;
    glViewport(0, 0, width, height);
}
