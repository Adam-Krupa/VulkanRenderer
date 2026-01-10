#include "../include/Application.hpp"
#include "../include/WindowsWindow.hpp"
#include "../include/Renderer.hpp"

Application::Application()
{
    WindowInfo info{};
    info.width = 1280;
    info.height = 720;
    info.tittle = "Vulcan Engine";

    window = std::make_unique<WindowsWindow>(info);
    renderer = std::make_unique<Renderer>(*window);
}

void Application::Run()
{
    while (running && !window->ShouldClose())
    {
        window->PollEvents();

        renderer->BeginFrame();
    //    renderer->DrawMesh();
        renderer->EndFrame();
    }
}