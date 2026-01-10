#include "../include/Renderer.hpp"
#include "../include/VulkanRenderer.hpp"



Renderer::Renderer(Window& window)
{
    BackendInitInfo info{};
    info.windowHandle = window.GetNativeHandle();
    info.width = window.GetWidth();
    info.height = window.GetHeight();

    backend = std::make_unique<VulkanRenderer>();
    backend->Init(info);
}

Renderer::~Renderer()
{
    backend->Shutdown();
}

void Renderer::BeginFrame()
{
    backend->BeginFrame();
}

void Renderer::DrawMesh(const MeshComponent& mesh)
{
    backend->DrawIndexed(6); // na razie quad
}

void Renderer::EndFrame()
{
    backend->EndFrame();
}