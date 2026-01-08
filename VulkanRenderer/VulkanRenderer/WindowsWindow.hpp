#pragma once
#include"./Window.hpp"
class WindowsWindow : public Window
{
    WindowsWindow(const WindowInfo& Params);
    virtual ~WindowsWindow() override;

    virtual void PollEvents() override;
    virtual bool ShouldClose() const override;

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    // dla backendów renderingu
    virtual void* GetNativeHandle() const override;
private: 
    WindowInfo WindowParams;
    class GLFWwindow* window = nullptr;
};

