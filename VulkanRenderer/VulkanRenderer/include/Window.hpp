#pragma once
#include<string>
struct WindowInfo {
	uint16_t width;
	uint16_t height;
	std::string tittle;
};
class Window
{
public:
    virtual ~Window() = default;

    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    // dla backendów renderingu
    virtual void* GetNativeHandle() const = 0;

};