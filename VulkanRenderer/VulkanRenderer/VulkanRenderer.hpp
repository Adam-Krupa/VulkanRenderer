#pragma once
#include "./Renderer.hpp"

class VulkanRenderer : public RendererBackend
{
public:
    void Init(const BackendInitInfo& info) override;
    void Shutdown() override;

    void BeginFrame() override;
    void DrawIndexed(uint32_t indexCount) override;
    void EndFrame() override;
};