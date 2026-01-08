#pragma once
#include "./Components.hpp"
#include "./Window.hpp"
#include <memory>
struct BackendInitInfo {
	void* windowHandle;
	uint32_t width;
	uint32_t height;
};
class Renderer
{
public:
	Renderer(Window& windowHandler);
	~Renderer();
	void BeginFrame();
	void DrawMesh(const MeshComponent& mesh);
	void EndFrame();

private:
	std::unique_ptr<class RendererBackend> backend;
};

class RendererBackend
{
public:
	RendererBackend();
	virtual ~RendererBackend() = default;
	virtual void Init(const BackendInitInfo& info) = 0;
	virtual void Shutdown() = 0;


	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;


	virtual void DrawIndexed(uint32_t indexCount) = 0;
};