#pragma once
#include<memory>
#include<string>
class Application
{
public:
	Application() = default;
	~Application() = default;
	void Run();

private:
	class std::unique_ptr<class Window> window;
	class std::unique_ptr<class Renderer> renderer;
	bool running = true;

};










