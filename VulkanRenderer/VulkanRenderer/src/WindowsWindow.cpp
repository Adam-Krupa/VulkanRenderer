#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

void* WindowsWindow::GetNativeHandle() const
{
    
    return window;
}

WindowsWindow::WindowsWindow(const WindowInfo& windowParams)
{
    WindowParams.width = windowParams.width;
    WindowParams.height = windowParams.height;
    WindowParams.tittle = windowParams.tittle;
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    window = glfwCreateWindow(WindowParams.width, WindowParams.height, WindowParams.tittle.c_str(), nullptr, nullptr);
}
