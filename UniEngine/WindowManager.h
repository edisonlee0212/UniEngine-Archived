#pragma once
#include "Misc.h"
#include "Core.h"
namespace UniEngine {
    class WindowManager
    {
    public:

        static GLFWwindow* CreateWindow(int, int);
        static int GetWidth() { return Width; }
        static int GetHeight() { return Height; }
        static GLFWwindow* GetWindow() { return window; }
        static void ResizeCallback(GLFWwindow*, int, int);

    private:
        static int Width;
        static int Height;
        static GLFWwindow* window;
    };

}
