#include "application.h"

Application::Application()
	:window(nullptr)
{
}

Application::~Application()
{
	delete rect;
	delete window;
}

void Application::Setup()
{
	window = new Window(SCRWIDTH, SCRHEIGHT, "OpenGL Framework");
	if (!window->Init())
	{
		std::cout << "Window initialization failed!" << std::endl;
		assert(false);
	}
	window->SetVSyncEnabled(true);
	Input::Init(window);

	rect = new Rect(100.0f, 100.0f, 50.0f, 50.0f);
	rect->SetPosition(vec2(200, 200));
	rect->SetSize(vec2(100, 100));
	rect->SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
	rect->SetTexture("res/textures/among us.png");
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 0.0f);
		HandleInput();

		// Draw
		rect->Draw();

		window->Display();
	}
}

void Application::HandleInput()
{
	window->PollEvents();

	if (Input::IsKeyPressed(GLFW_KEY_W)) 
		std::cout << "W key is pressed!" << std::endl;
}

void Application::Run()
{
	Setup();
	Update();
}
