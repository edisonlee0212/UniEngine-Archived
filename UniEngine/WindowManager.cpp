#include "WindowManager.h"
using namespace UniEngine;

int WindowManager::Height;
int WindowManager::Width;
GLFWwindow* WindowManager::window;


void WindowManager::ResizeCallback(GLFWwindow* window, int width, int height) {
    Width = width;
    Height = height;
    glViewport(0, 0, width, height);
}
GLFWwindow* WindowManager::CreateWindow(int width, int height) {
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "Tree Engine", NULL, NULL);
    WindowManager::Width = width;
    WindowManager::Height = height;
    if (window == NULL)
    {
        Debug::Error("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    return window;
}
